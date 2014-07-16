# parsley

C++ XML and Plain text parser

Parsley is a light-weight, efficient and simple-to-use C++ XML and plain-text parsing library.
It includes two sets of classes, one is a traditional XML Parser that loosely follows the
Document Object Model (DOM) and the other is a plain text navigation program that enables 
you to easily move around a text file. 

Full documentation for all methods and classes is available via the Doxyfile.
To use it, download Doxygen and simply call `doxygen Doxyfile from a command
line.

## Example usage: XMLParsley

The XML Parser is made up of two classes: XMLNode, which represents a single node in
an XML document and XMLParsley, which is the main parsing engine that converts between
XML documents and XMLNodes. 

Let's use this XML document as an example (text.xml):

```xml
<?xml version="1.0" encoding="UTF-8"?>
<menu>
	<dish>
		<name>French fries</name>
		<price>$3.90</price>
		<description>
		Fresh potatoes, fried with love.
		</description>
		<calories>550</calories>
	</dish>
</menu>

```

Here is an example program that uses the XML Parser and the above xml file:

```cpp
#include "Parsley.h"
#include <iostream>

int main(int argc, char * argv[])
{
    // This XMLNode pointer will be the root for the xml document
    XMLNode* root;
    
    // The XMLParsley class parses the test.xml document. It has
    // two methods, parse() and save() and it stores neither
    // the filename nor the XMLNode, meaning you must take care
    // of calling the save() method before exiting your program
    // if you want to save the XML document back to a file.
    // It also means, however, that you can get rid of
    // the parser if you don't need it anymore after parsing
    // a document.
    XMLParsley parser;
    
    // Store the file name
    std::string fname("/Users/petergoldsborough/Documents/C++/Exercises/Exercises/test.xml");
    
    // Call the parse() method to parse an xml document. It then
    // returns (if all went well) the root node of the document.
    root = parser.parse(fname);
    
    // We now have access to the entire tree.
    XMLNode* firstChild = root->getFirstChild();
    
    //Lets change the first child's tag name.
    firstChild->setTag("changedTagName");
    
    // It's also good to know where our food is from
    firstChild->addAttr("origin", "Belgium");
    
    // We're also adding a 10% tax due to a critical ice cream
    // shortage in our region, forcing us to import it from
    // the north pole.
    firstChild->getElementsByTagName("price")[0]->setData("$4.29");
    
    // We can create a new XMLNode. Its constructor takes the tag
    // name for the new XML node.
    XMLNode* child = new XMLNode("dish");
    
    // We can give it an attribute
    child->addAttr("time", "lunch");
    
    // Let's also put something between the tags
    child->setData("KFC with ketchup and caviar");
    
    // Adding a new XMLNode to an existing one is very easy
    root->appendChild(child);
    
    // Did it work?
    std::cout << root->getLastChild()->getData() << std::endl
              << root->getNthChild(1)->getAttr("time") << std::endl;
    
    // This should output:
    // >>> KFC with ketchup and caviar
    // >>> lunch
    
    // Finally, if you want to save the XML document, call the parser's
    // save() method to store the XML tree back into a file. By default,
    // this also destroys the tree. If you want to keep on using the tree
    // or maybe save it into multiple files, set the third argument to false
    // as I have here. This means you must take care of deleting the tree
    // yourself afterwards.
    parser.save(root, fname, false);
    
    // Which would be done like so:
    delete root;
    
    // Note that as soon as you make a new node part of at tree like we
    // did here for "child", you only need to delete the root. Let recursion
    // take care of the rest.
}
```

This creates this new XML file (test.xml):

```xml
<?xml version="1.0" encoding="UTF-8"?>
<menu>
    <changedTagName origin="Belgium">
        <name>French fries</name>
        <price>$4.29</price>
        <description>
        Fresh potatoes, fried with love.
        </description>
        <calories>550</calories>
    </changedTagName>
    <dish time="lunch">KFC with ketchup and caviar</dish>
</menu>
```

Of course there are a lot more possibilites to manipulate the XML nodes.
Have a look at the documentation or the Parsley header file for all options.

Examples for TextParsley to follow.