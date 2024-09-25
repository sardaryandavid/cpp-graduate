#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>

namespace caches {

template <typename T, typename KeyT>
struct page_t {
private:
  T data_;
  KeyT key_;

public:
  page_t(KeyT key) : key_(key) {}
  KeyT get_key() const { return key_; }
  T get_data() const { return data_; }
  void set_data(T data) { data_ = data; }

  /* WARNING: use only if KeyT and T are int */
  int slow_get_page_int() { data_ = key_; return data_; };
};

namespace lfu {
  enum class ret_t { NOT_EXIST = 0, EXIST};

  /* elem_node_t is a node of node list in the article */
  template <typename PageT, typename FreqNodeT>
  struct elem_node_t {
  using FreqNodeIt = typename std::list<FreqNodeT>::iterator;

  private:
    PageT page_;
    FreqNodeIt freq_node_it_;

  public:
    elem_node_t(PageT page, FreqNodeIt freq_node_it) : page_(page), 
                                                       freq_node_it_(freq_node_it) {};
    
    PageT get_page() const { return page_; }
    FreqNodeIt get_freq_node_it() const { return freq_node_it_; }
  };

  template <typename T, typename KeyT = int> 
  struct freq_node_t {
  using ElemList = typename std::list<elem_node_t<page_t<T, KeyT>, freq_node_t<T, KeyT>>>;
  using ElemListIt = typename std::list<elem_node_t<page_t<T, KeyT>, freq_node_t<T, KeyT>>>::iterator;
  using NodeT = elem_node_t<page_t<T, KeyT>, freq_node_t<T, KeyT>>;
  using HashT = std::unordered_map<KeyT, ElemListIt>;

  private:
    int freq_;
    ElemList elem_list_; 

  public:
    freq_node_t(int freq) : freq_(freq) {}
    const ElemList& get_elem_list() const { return elem_list_; }

    KeyT get_key_first_elem() const { 
      auto elem_node_it = elem_list_.begin();
      return elem_node_it->get_page().get_key();
    }
    void erase_elem(ElemListIt elem_node_it) { elem_list_.erase( elem_node_it); }
    void erase_first_elem() { elem_list_.pop_front(); }
    void push_elem_front(NodeT elem) { elem_list_.push_front(elem); }
    void insert_first_elem_to_hash(HashT& hash, KeyT key) {
      auto elem_it = elem_list_.begin();
      hash.emplace(key, elem_it);
    }
    int get_freq() const { return freq_; }
  };

  template <typename T, typename KeyT = int> 
  struct cache_t {
  using ElemListIt = typename std::list<elem_node_t<page_t<T, KeyT>, freq_node_t<T, KeyT>>>::iterator;

  private:
    size_t sz_ = 0;
    size_t cp_;
    std::list<freq_node_t<T, KeyT>> freq_list_;
    std::unordered_map<KeyT, ElemListIt> hash_;

  public:
    cache_t(size_t cp) : cp_(cp) {}

    bool full() const { return (sz_ >= cp_); }

    ret_t insert(KeyT key) {
      #ifdef DEBUG
      print_cache_t();
      #endif

      auto hash_elem_it = hash_.find(key);
      if (hash_elem_it != hash_.end())
        return ret_t::EXIST;

      if (full()) {
        auto freq_node_it = freq_list_.begin();
        auto key = freq_node_it->get_key_first_elem();
        auto hash_elem_old_it = hash_.find(key);
        
        freq_node_it->erase_first_elem();
        hash_.erase(hash_elem_old_it);
        --sz_;

        if (sz_ == 0)
          freq_list_.pop_front();
      }

      if (freq_list_.empty() || freq_list_.front().get_freq() != 1) {
        freq_node_t<T, KeyT> freq_node{1};
        freq_list_.push_front(freq_node);
      }

      auto freq_node_it = freq_list_.begin();
      page_t<T, KeyT> page{key};
      page.slow_get_page_int();
      elem_node_t<page_t<T, KeyT>, freq_node_t<T, KeyT>> elem{page, freq_node_it};
      freq_node_it->push_elem_front(elem);
      freq_node_it->insert_first_elem_to_hash(hash_, key);
      ++sz_;

      return ret_t::NOT_EXIST;
    }

    void access(KeyT key) {
      auto hash_elem_it = hash_.find(key);
      if (hash_elem_it == hash_.end())
        return;

      auto elem_node_it = hash_elem_it->second;
      auto freq_node_it = elem_node_it->get_freq_node_it();
      auto next_freq_node_it = std::next(freq_node_it, 1);

      if ((next_freq_node_it == freq_list_.end()) ||
          (next_freq_node_it->get_freq() != freq_node_it->get_freq() + 1)) {
        freq_node_t<T, KeyT> new_freq_node{freq_node_it->get_freq() + 1};
        next_freq_node_it = freq_list_.insert(next_freq_node_it, new_freq_node);
        ++sz_;
      }

      page_t<T, KeyT> page{key};
      page.set_data(elem_node_it->get_page().get_data());
      elem_node_t<page_t<T, KeyT>, freq_node_t<T, KeyT>> elem{page, next_freq_node_it};

      freq_node_it->erase_elem(elem_node_it);
      hash_.erase(hash_elem_it);

      next_freq_node_it->push_elem_front(elem);
      next_freq_node_it->insert_first_elem_to_hash(hash_, key);

      if (freq_node_it->get_elem_list().empty()) {
        freq_list_.erase(freq_node_it);
        --sz_;
      }
    }

    void print_cache_t() const {
      std::cout << "-------------" << std::endl;
      for (auto freq_node : freq_list_) {
        std::cout << "FREQUENCY " << freq_node.get_freq() << " START\n";
        for (auto elem_node : freq_node.get_elem_list()) {
          std::cout << elem_node.get_page().get_data() << std::endl;
        }
        std::cout << "FINISH\n";
      }
      std::cout << "-------------" << std::endl;
    }
  };

  size_t count_hits(size_t m, size_t n, std::vector<int> data) {
  size_t hits = 0;
  caches::lfu::cache_t<int> c{m};
    for (size_t i = 0; i < n; ++i) {
    if (c.insert(data[i]) == ret_t::EXIST) {
      c.access(data[i]);
      hits += 1;
    } 
  }

  return hits;
  }
} // namespace lfu

namespace belady {
  template <typename T>
  struct cache_t {
  private:
    size_t cp_;
    size_t sz_ = 0;
    std::vector<T> cache_;
  
  public:
    cache_t(size_t cp) : cp_(cp) {}

    bool full() const { return (cp_ == sz_); }
    size_t get_cp() const { return cp_; }
    
    /* WARNING: use in full cache */
    void set(T val, size_t pos) { cache_[pos] = val; }

    void insert(T val) {
      if (full())
        return;

      cache_.push_back(val);
      ++sz_;
    }

    bool is_exist(T val) const {
      if (std::find(cache_.begin(), cache_.end(), val) != std::end(cache_))
        return true;
      
      return false;
    }

    size_t most_far(std::vector<T> data, size_t curr_pos) {
      size_t data_sz = data.size();
      size_t most_far_elem_pos = curr_pos + 1;
      size_t most_far_elem_cache_pos = 0;
      size_t pos;
      
      /* Here is no ++sz_, because this elem will be deleted after the loop */
      cache_.push_back(data[curr_pos]);
      for (size_t i = 0; i <= cp_; ++i) {
        pos = curr_pos + 1;

        while (pos < data_sz && (data[pos] != cache_[i]))
          ++pos;
      
        if (pos > most_far_elem_pos) {
          most_far_elem_pos = pos;
          most_far_elem_cache_pos = i;
        }
      }
      cache_.pop_back();

      return most_far_elem_cache_pos;
    }

    void print_cache_t() const {
      std::cout << "---------------\n";
      for (size_t i = 0; i < sz_; ++i)
        std::cout << cache_[i] << " ";
      std::cout << "\n---------------\n";
    }
  };

  size_t count_hits(size_t m, size_t n, std::vector<int> data) {
    size_t hits = 0;
    caches::belady::cache_t<int> c{m};

    for (size_t i = 0; i < n; ++i) {
      if (c.is_exist(data[i]))
        ++hits;

      else if (c.full()) {
        size_t most_far_elem_cache_pos = c.most_far(data, i);

        /* most_far_elem_cache_pos is capacity if we shouldn't cache new elem */
        if (most_far_elem_cache_pos != c.get_cp())
          c.set(data[i], most_far_elem_cache_pos);
      }

      else
        c.insert(data[i]);
      
      #ifdef BDEBUG
      c.print_cache_t();
      #endif
    }

    return hits;
  }
} // namespace belady

} // namespace caches