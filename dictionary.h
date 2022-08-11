
#include "iostream"
#include "vector"
#ifndef DRWEB_DICTIONARY_H
#define DRWEB_DICTIONARY_H


template<class Key, class Value>
class dictionary
{
public:
    virtual ~dictionary() = default;

    virtual const Value& get(const Key& key) const = 0;
    virtual void set(const Key& key, const Value& value) = 0;
    virtual bool is_set(const Key& key) const = 0;
};
template<class Key>
class not_found_exception : public std::exception
{
public:
    virtual const Key& get_key() const noexcept = 0;
};
template<class Key>
class already_exist_exception : public std::exception
{
public:
    virtual const Key& get_key() const noexcept = 0;
};

template<class Key, class Value>
class names : public dictionary<Key , Value>
{
private:
    class not_found : public not_found_exception<Key> {
    private:
        Key key_;
        std::string message_;
    public:
        const Key& get_key() const noexcept override {
            return key_;
        }
        void set_key(const Key& key) noexcept {
            key_ = key;
        }
        explicit not_found(Key key) {
            set_key(key);
            message_ = "not_found key: " + get_key();
        }
        [[nodiscard]] const char* what() const noexcept override {return message_.data();}
    };
    class already_exist : public already_exist_exception<Key> {
    private:
        Key key_;
        std::string message_;
    public:
        const Key& get_key() const noexcept override {
            return key_;
        }
        void set_key(const Key& key) noexcept {
            key_ = key;
        }
        explicit already_exist(Key key) {
            set_key(key);
            message_ = "already exist element by key: " + get_key();
        }
        [[nodiscard]] const char* what() const noexcept override {return message_.data();}
    };
    std::vector<std::pair<Key, Value>> data_;

public:
    names() {
        data_.resize(0);
    }
    ~names() override = default;

    const Value& get(const Key& key) const override {
        for (int el = 0; el < data_.size(); el++) {
            if (data_[el].first == key) {
                return data_[el].second;
            }
        }
        throw not_found(key);
    }

    void set(const Key& key, const Value& value) override {
        if (!is_set(key))
            data_.push_back(std::make_pair(key, value));
        else
            throw already_exist(key);

    }

    bool is_set(const Key& key) const override {
        for (int el = 0; el < data_.size(); el++) {
            if (data_[el].first == key)
                return true;
        }
        return false;
    }
};

#endif //DRWEB_DICTIONARY_H
