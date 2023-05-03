import random;  
filename = '书籍学习笔记\Effective C++\EffectCppPractice\programming.txt'
with open(filename, 'a') as file_object:
    for i in range(30000):    
        ret = random.uniform(1.0, 100.0)    
        file_object.write(str(ret) + '\n')
