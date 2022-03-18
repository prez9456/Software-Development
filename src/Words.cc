#include "Words.h"
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>

using namespace std;

Words::Words(string input){
    analyze(input);
}

Words::Words(const Words &rhs) : vec(rhs.vec), boolvec(rhs.boolvec) {}

Words &Words::operator=(const Words &rhs){
    vec = rhs.vec;
    boolvec = rhs.boolvec;
    return *this;
}

Words Words::operator+(const Words &rhs) const{
    Words retval = *this;
    return retval += rhs;
}

Words &Words::operator+=(const Words &rhs){
    vec.insert(vec.end(), rhs.vec.begin(), rhs.vec.end());
    boolvec.insert(boolvec.end(), rhs.boolvec.begin(), rhs.boolvec.end());
    return *this;
}

bool Words::operator!=(const Words &rhs) const{
    return !(*this == rhs);
}

bool Words::operator==(const Words &rhs) const{
    if(this->size() != rhs.size()){
        return false;
    }
    for(size_t i = 0; i < size(); i++){
        if(this->vec[i] != rhs.vec[i]){
            return false;
        }
    }
    return true;
}

Words::operator bool() const{
    return (size() > 0);
}

Words &Words::operator--(){
    bool abort;

    for(size_t i = 0; i < vec.size(); i++){
        if(vec[i] != ""){
            abort = false;
            break;
        }
        else{
            abort = true;
        }
    }
    if(abort){
        vec.clear();
        return *this;
    }

    for(size_t j = 0; j < vec.size(); j++){
        if(vec[j] == ""){
            vec.erase(vec.begin()+j);
        }
        if(vec[j].length() > 0){
            vec[j].pop_back();
        }
    }
    return *this;
}

Words Words::operator--(int){
    const auto save = *this;
    --*this;
    return save;
}

Words::parts& Words::operator[](size_t x) {
    Words temp = *this;

    if((temp.get(x, p.first, p.second)) == false ){
        cout << "Index was:" << x << " and size of object is:"<< vec.size();
        throw out_of_range("Try again");
    }

    return p;
}

void Words::word_recognition(string word){
    int end = word.length();
    string phrase = "";
    string open_paren = "(";
    string closed_paren = ")";
    for(int i = 0; i < end; i++){
        if(word[i] == '\\'){
            phrase += word[i+1];
            boolvec.push_back(true);
            i += 2;
        }
        if(isspace(word[i])){
            if(phrase.length() > 0){
                vec.push_back(phrase);
                boolvec.push_back(false);
                phrase.clear();
            }
            continue;
        }
        if(word[i] == '('){
            if(phrase.length() > 0){
                vec.push_back(phrase);
                boolvec.push_back(false);
                phrase.clear();
            }
            vec.push_back(open_paren);
            boolvec.push_back(false);
            continue;
        }
        if(word[i] == ')'){
            if(phrase.length() > 0){
                vec.push_back(phrase);
                boolvec.push_back(false);
                phrase.clear();
            }
            vec.push_back(closed_paren);
            boolvec.push_back(false);
            continue;
        }
        phrase += word[i];
        if (i == end-1 && phrase.length() > 0){
            vec.push_back(phrase);

        }
    }    
}

void Words::analyze(string word){
    vec.clear();
    boolvec.clear();
    word_recognition(word);
}

size_t Words::size() const{
    return vec.size();
}

bool Words::empty() const{
    if(vec.size() == 0){
        return true;
    }
    return false;
}

bool Words::get(size_t n, string &chars, bool &check) const{
    if (n > size()) {
        check = false;
        return false;
    }
    chars = vec[n];
    check = boolvec[n];
    return true;
   
}

ostream &operator<<(ostream &os, const Words &out){
    for(size_t i = 0; i < out.size(); i++){
		if (i == out.size()-1){
		    os << out.vec[i];
		}
        else{
		    os << out.vec[i] << ",";
        }
	}
	return os;
}