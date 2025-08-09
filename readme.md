#Предназначение
Этот текстовый редактор разрабатывается для более удобной работы с текстом, в отличии от работы с текстом в MS Word.
И разрабатывается как более легковесный редактор под кроссплатформы с отркрытым исходным кодом на QT Widgets.
На данный момент работать с ним удобно с небольшим текстом.

#Purpose
This text editor is designed to work with text more conveniently, unlike working with text in MS Word.
And it is being developed as a more lightweight editor for cross-platforms with open source code on QT Widgets.
At the moment, it is convenient to work with it with a small text.

#Использование
В тексте вставляются специальные конструкции:
"!!название_класса_со_стилем-" - устанавливает стиль текста из класса для всего текста идущего после конструкции
"%название_текстовой_переменной" - заменяет текст на текст, хранящийся в созданной вами переменной
Переменная создаётся: В поле для определения переменных (слева сверху) вводится следующим образом -> название_переменной=значение переменной
В переменную идут все символы до переноса строки.

Пример 
[Поле переменных]
ФИО=И.И.Иван
полноеФИО=Иванов Иван Иванович 

[Поле ввода]
!!мой_стиль-Меня зовут %полноеФИО, сокращенно !!другой_стиль-%ФИО

#Usage
Special constructions are inserted in the text:
"!!class_name_style-" - sets the style of the text from the class for all text following the construction
"%text_name_variable" - replaces the text with the text stored in the variable you created
A variable is created: In the field for defining variables (top left), enter as follows -> the name of the variable=the value of the variable
All characters before the line break go to the variable.

Example 
[Variable field]
name=Robert
full_name=Robert Striniv 

[Input field]
!!my_style- My name is %full_name, for short!!other_style-%name
