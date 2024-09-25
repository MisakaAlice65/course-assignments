#include <iostream>  
#include <cstring>  
  
class Chicken  
{  
    private:  
        int age = 24;  
        char *name = nullptr;  
  
    public:  
        Chicken() {}; 
  
        Chicken(int _age) : age(_age) {};  //Chicken c1(35);
  
        Chicken(int _age, const char *_name) : age(_age)  
        {  
            setName(_name);  
        };  
  

        
        //���ƹ��캯�����ڴ����¶���
        
    	//��ֵ��������ڸ����Ѿ����ڵĶ���
        
        
        // ���ƹ��캯�� ����������ж���ĸ��� 
        Chicken(const Chicken& other) : age(other.age)   
        {                                               
            setName(other.name);  
        };  
  
        ~Chicken()  //�������ʱ�Զ����ã���ֹ�ڴ�й¶ 
        {  
            if (name != nullptr)  
                delete[] name;  
        }  
  
        // ��ֵ����������¶��� 
        Chicken& operator=(const Chicken& other)      //Chicken c3 = c1; ����//Chicken c3;   c3=c1; 
        {  
            if (this != &other)  
            {  
                setAge(other.age);  
                setName(other.name);  
            }  
            return *this;  
        }  
  
        void setAge(int _age)  
        {  
            age = _age;  
        }  
  
        void setName(const char *_name)  
        {  
            if(name != nullptr)  
                delete[] name;  
            int len = strlen(_name) + 1;  
            name = new char[len];  
            strcpy(name, _name);  
        }  
  
        const char *getName() const  
        {  
            return name;  
        }  
  
        int getAge() const  
        {  
            return age;  
        }  
};  
