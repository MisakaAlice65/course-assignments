#include "List.h"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    List<int> intList;
    //初始化列表构造函数
    List<int> lst1 = {1, 2, 3, 4, 5};
    for (const auto &value : lst1) {  
        std::cout << value << " ";  
    }  
    std::cout << std::endl;  


    // Test push_front and push_back.
    for (int i=1;i<10;i++){
        intList.push_back(i);
    }
    intList.push_front(0);


    // Test size and empty.
    std::cout << "intList size: " << intList.size() << ", empty: " << (intList.empty() ? "true" : "false") << std::endl;
  
    // Test front and back.
    std::cout << "intList front: " << intList.front() << ", back: " << intList.back() << std::endl;
  
    // Test iterator.
    for (List<int>::iterator it = intList.begin(); ++it != intList.end(); ) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (List<int>::iterator it = intList.begin(); it++ != intList.end(); ) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    // Test reverse iterator with -- operator.  
    std::cout << "intList reverse: ";  
    for (List<int>::iterator it = intList.end(); it-- != intList.begin(); ) {  
        std::cout << *it << " ";  
    }  
    std::cout << std::endl;  

    

    for (List<int>::iterator it = intList.end(); --it != intList.begin();) {  
        std::cout << *it << " ";  
    }  
    std::cout << std::endl;  
    
    // Test clear.
    intList.clear();

    std::cout << "intList size: " << intList.size() << ", empty: " << (intList.empty() ? "true" : "false") << std::endl;
    
    for (int i=1;i<10;i++){
        intList.push_back(i);
    }
    intList.push_front(0);

    // Test copy constructor and assignment operator.
    List<int> intListCopy(intList);

    List<int> intListAssign;

    intListAssign = intListCopy;

    for (const auto &value : intListCopy) {  
        std::cout << value << " ";  
    }  
    std::cout << std::endl;  

    for (const auto &value : intListAssign) {  
        std::cout << value << " ";  
    }  
    std::cout << std::endl;  

    // Test insert and erase and pop_back and pop_front.
    intList.insert(intList.begin(), 3);

    for (const auto &value : intList) {  
        std::cout << value << " ";  
    }  
    std::cout << std::endl;  

    intList.erase(intList.begin());

    for (const auto &value : intList) {  
        std::cout << value << " ";  
    }  
    std::cout << std::endl;  

    intList.pop_back();
    for (const auto &value : intList) {  
        std::cout << value << " ";  
    }  
    std::cout << std::endl;  

    intList.pop_front();
    for (const auto &value : intList) {  
        std::cout << value << " ";  
    }  
    std::cout << std::endl;  


    // Test move.

    List<int> lst2 = std::move(intList);
    for (const auto &value : lst2) {  
        std::cout << value << " ";  
    }  
    std::cout << std::endl;  


    return 0;
}
