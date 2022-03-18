#ifndef WORDS_H_INCLUDED
#define WORDS_H_INCLUDED

#include <string>
#include <vector>

class Words {
    public:
    struct parts{
        std::string first;
        bool second;
        } p;
        
        Words(std::string);
        Words(const Words &);
        Words() = delete;
        ~Words() = default;
        
        Words &operator=(const Words&); 

        // HW5 Addition
        Words operator+(const Words&) const;
        Words &operator+=(const Words&);
        bool operator!=(const Words&) const;
        bool operator==(const Words&) const;
        explicit operator bool() const;
        Words &operator--(); // Prefix
        Words operator--(int); // PostFix
        parts &operator[](size_t);
        
        void word_recognition(std::string);
        void analyze(std::string);
        [[nodiscard]] size_t size() const;
        [[nodiscard]] bool empty() const;
        bool get(size_t, std::string&, bool&) const;
        friend std::ostream &operator<<(std::ostream &os, const Words &out);
        
    private:
        std::vector<std::string> vec;
        std::vector<bool> boolvec;
};
#endif