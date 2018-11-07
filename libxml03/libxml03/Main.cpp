#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib,"libxml2.lib")
#pragma comment(lib,"iconv.lib")

#include <conio.h>
#include <stdio.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
//#include <libxml/encoding.h>
//#include <libxml/xmlwriter.h>
#include <libxml/HTMLparser.h>
#include <libxml/xmlreader.h>

void traverse_dom_trees(xmlNode*a_node)
{
	xmlNode*cur_node = NULL;
	if(NULL == a_node)
	{
		//printf("Invalid argument a_node %p\n", a_node);
		return;
	}
	
	for(cur_node = a_node; cur_node; cur_node = cur_node->next)
	{
		if(cur_node->type == XML_ELEMENT_NODE)
		{
			/* Check for if current node should be exclude or not */
			printf("EleNode type: %s\n", cur_node->name);

			xmlAttr* attribute = cur_node->properties;
			while(attribute)
			{
				//xmlChar* value = xmlNodeListGetString(cur_node->doc, attribute->children, 1);

				printf("EleAttr: %s - Contents: %s\n", attribute->name, (char *)attribute->children->content);

				//xmlFree(value);//do something with value
				attribute = attribute->next;
			}

		}

		if(cur_node->type == XML_TEXT_NODE)
		{
			/* Process here text node, It is available in cpStr :TODO: */
			printf("TxtNode Content: %s - Content Length %d\n", (char *)cur_node->content, strlen((char *)cur_node->content));
		}
		traverse_dom_trees(cur_node->children);
	}
}

int main(int argc, char**argv)
{
	htmlDocPtr doc;
	xmlNode *roo_element = NULL;
	
	if (argc != 2)
	{
		printf("\nInvalid argument\n");
		return(1);
	}

    /* Macro to check API for match with the DLL we are using */
    //LIBXML_TEST_VERSION
	
	doc = htmlReadFile(argv[1], NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
	if (doc == NULL)
	{
		fprintf(stderr, "Document not parsed successfully.\n");
		return 0;
	}
	roo_element = xmlDocGetRootElement(doc);
	if (roo_element == NULL)
    {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return 0;
    }
	printf("Root Node is %s\n", roo_element->name);
	traverse_dom_trees(roo_element);

    xmlFreeDoc(doc);    //free document
    xmlCleanupParser(); //Free globals

	getchar();
    return 0;
}