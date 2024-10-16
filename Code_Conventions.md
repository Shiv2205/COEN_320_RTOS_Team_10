
# Naming Conventions
- **Variables/Pointers:**
```c++
//snake-case
int example_var_name;

//Notice how the asterisk(*) is glued to the data type. 
//Meaning example_pointer_definition is of type "Integer pointer" (int*), and not just integer
int* example_pointer_definition;
```

- **Functions:**
```c++
//Capitalize first letter of first word in the name
int Example_function_name(int some_parameter);

//If function has no parameter include "void"
void Second_example(void);
```

- **Classes:**
```c++
//Either one word
class Person {}

//Or if >1 word in required:
//Capitalize first letter of every word in the name
class Degree_Requirements {} 
```

# Code Style

- **Indentation and code blocks:**
```c++
int Some_function(void)
{//Code blocks start after definition

  //Indentation are 2 spaces. Using actual space characters and not Tab
  //Replacing Tabs with spaces can be configured in most IDEs/Text editors
  int example_var_name = 0;
  if(!example_var_name)
  {
    example_var_name++;
  }
  return example_var_name;
}
``` 
