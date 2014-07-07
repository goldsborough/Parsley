//
//  Parsley.h
//
//  Created by Peter Goldsborough on 19/04/14.
//  Copyright (c) 2014 Peter Goldsborough. All rights reserved.
//

#ifndef __Parsley__
#define __Parsley__

#include <string>
#include <vector>
#include <map>

class XMLNode;

typedef std::string::iterator str_Itr;
typedef std::string::const_iterator str_cItr;

typedef std::vector<std::string>::const_iterator vec_cItr;

std::string condense(str_cItr begin, str_cItr end);

std::string strip(str_cItr begin, str_cItr end);

std::vector<std::string> split(str_cItr begin, str_cItr end);

std::string join(vec_cItr begin, vec_cItr end);

std::string splitOne(str_cItr begin, str_cItr end);

void deleteXMLTree(XMLNode * tree);

class TextParsley
{
    
public:
    
    TextParsley()
    : _saved(0)
    { }
    
    ~TextParsley()
    { save(); }
    
    void openFile(const std::string& fname);
    void newFile(const std::string& fname);
    
    void save();
    
    std::string currWord()
    { return *_currWord; }
    
    std::string currLine()
    { return join(_currLine->begin(), _currLine->end()); }
    
    void appendToLine(const std::string& str);
    
    void appendToFile(const std::string& str)
    {
        _file.push_back(split(str.begin(), str.end()));
        
        toFileEnd();
    }
    
    void insertInLine(const std::string& str);
    
    void insertInFile(const std::string& str)
    { _currLine = _file.insert(_currLine, split(str.begin(),str.end()));}
    
    void eraseWord();
    
    void eraseLine();
    
    void replaceWord(const std::string& str);
    
    void replaceLine(const std::string& str);
    
    void toLineStart()
    { _currWord = _currLine->begin(); }
    
    void toFileStart()
    {
        _currLine = _file.begin();
        _currWord = _currLine->begin();
    }
    
    void toLineEnd()
    { _currWord = _currLine->end() - 1; }
    
    void toFileEnd()
    {
        _currLine = _file.end() - 1;
        _currWord = _currLine->begin();
    }
    
    void moveWord(int count)
    { std::advance(_currWord, count); }
    
    void moveLine(int count)
    { std::advance(_currLine, count); }
    
    std::vector<std::string> readAllItems();
    std::vector<std::string> readAllLines();
    
private:
    
    typedef std::vector<std::string> wordVec;
    typedef std::vector<std::vector<std::string>> lineVec;
    
    typedef wordVec::iterator wordItr;
    typedef lineVec::iterator lineItr;
    
    lineVec _file;
    
    wordItr _currWord;
    lineItr _currLine;
    
    std::string _fname;
    
    bool _saved;
};

class XMLNode
{
    
public:
    
    typedef std::vector<XMLNode*> NodeVec;
    typedef NodeVec::const_iterator NodeVec_cItr;
    
    bool getAttr(std::string& str, const std::string& attrKey);
    
    bool findAttr(const std::string& key)
    { return attrs.find(key) != attrs.end(); }
    
    void addAttr(const std::string& key, const std::string& val)
    { attrs[key] = val; }
    
    // Only sets/changes an attribute if it exists, else it will
    // create attributes for each typo or something
    void setAttr(const std::string& key, const std::string& val)
    { if (findAttr(key)) addAttr(key, val); }
    
    bool removeAttr(const std::string& key);
    
    std::string getTag() { return tag; }
    void setTag(const std::string& name) { tag = name; }
    
    NodeVec getElementsByTagName(const std::string& tagName);
    NodeVec getElementsByAttrName(const std::string& attrName);
    
    std::string getData() const { return data; }
    std::string::size_type getDataLength() const { return data.size(); }
    
    bool hasData() const { return ! data.empty(); }
    
    void setData(const std::string& newData) { data = newData; }
    void appendData(const std::string& newData) {data += newData; }
    
    void insertData(const std::string::size_type ind, const std::string& newData)
    { data.insert(ind, newData); }
    
    void replaceData(const std::string& oldData, const std::string& newData)
    { data.replace(oldData.begin(), oldData.end(), newData); }
    
    std::string splitData(const std::string::size_type ind)
    { return data.substr(ind); }
    
    std::string substringData(const std::string::size_type ind,
                              std::string::size_type count = std::string::npos)
    { return data.substr(ind,count); }
    
    void deleteData() { data.erase(); }
    
    XMLNode* getParent() const { return parent; }
    XMLNode* getPrevSibling() const { return prevSibling; }
    XMLNode* getNextSibling() const { return nextSibling; }
    XMLNode* getFirstChild() const { return firstChild; }
    XMLNode* getLastChild() const { return lastChild; }
    
    bool isLastChild() const
    { return parent->lastChild != 0 && this == parent->lastChild; }
    
    bool isFirstChild() const
    { return parent->lastChild != 0 && this == parent->firstChild; }
    
    bool hasChildren() const { return firstChild != 0 && lastChild != 0; }
    
    bool hasParent() const { return parent; }
    
    void prependChild(XMLNode * node);
    void appendChild(XMLNode* node);
    
    bool insertChild(XMLNode* childOfThisNode, XMLNode * node);
    bool removeChild(XMLNode* childOfThisNode);
    
    void removeFirstChild() { removeChild(firstChild); }
    void removeLastChild() { removeChild(lastChild); }
    
private:
    
    friend class XMLParsley;
    friend void deleteXMLTree(XMLNode* node);
    
    typedef std::map<std::string,std::string> AttrMap;
    
    AttrMap attrs;
    
    std::string tag;
    
    std::string data;
    
    XMLNode* parent       = 0;
    
    XMLNode* prevSibling  = 0;
    XMLNode* nextSibling  = 0;
    
    XMLNode* firstChild   = 0;
    XMLNode* lastChild    = 0;
    
    bool isClosed = false;
    bool selfClosed = false;
};

class XMLParsley
{
    
public:
    
    XMLParsley() { };
    XMLParsley(const std::string& fname) { parse(fname); }
    XMLParsley(XMLNode * root, const std::string& fname)
    : _root(root), _fname(fname) { }
    
    ~XMLParsley() { close(); }
    
    XMLNode * parse(const std::string& fname);
    void parse(XMLNode * root, const std::string& fname)
    { _root = root; _fname = fname; }
    
    void close() { if (! _saved) save(_root); }
    
    void save(XMLNode * root);
    
private:
    
    typedef std::vector<std::string> StrVec;
    
    typedef StrVec::const_iterator StrVec_cItr;
    
    XMLNode * _makeNode(str_cItr begin, str_cItr end, bool docHead = false);
    
    StrVec_cItr _makeNodeTree(StrVec_cItr itr, StrVec_cItr end, XMLNode * parent);
    
    std::vector<std::string> _parse(str_cItr begin, str_cItr end);
    
    bool isSelfClosing(str_cItr begin, str_cItr end) const;
    
    XMLNode::AttrMap getAttrs(str_cItr begin, str_cItr end) const;
    
    template <class T>
    T lastNonSpace(T begin, T end);
    
    bool isHeader(str_cItr begin, str_cItr end);
    
    std::string _nodeToString(const XMLNode * node, std::string indent = "", bool docHead = false) const;
    std::string _treeToString(const XMLNode * root, std::string& str, std::string indent = "") const;
    
    std::string _fname;
    
    bool _open;
    bool _saved;
    bool _hasHeader;
    
    XMLNode * _root;
    
};

#endif /* defined(__Parsley__) */
