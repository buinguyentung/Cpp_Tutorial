#include "WorkItem.h"

/*WorkItem::WorkItem(const char* message, int number)
{
    m_message = message;
    m_number = number;
}

WorkItem::~WorkItem()
{

}

const char* WorkItem::getMessage() {
    return m_message.c_str();
}

int WorkItem::getNumber() {
    return m_number;
}
*/
bool sortLexicographically(char* a, char* b) {
    return strcmp(a, b) < 0;
}
