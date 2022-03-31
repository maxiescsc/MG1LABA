#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>

GLuint VBO; // переменная для хранения указателя на буфер вершин
static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT); // очищает буфер цвета
	glEnableVertexAttribArray(0); // индексация

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // привязываем буфер для приготавливания его для отрисовки

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // как воспринимать данные внутри буфера(шейдеры, кол-во компонентов, тип данных, нормализация атрибута)

	glDrawArrays(GL_TRIANGLES, 0, 3); // рисуем все


	glDisableVertexAttribArray(0); // отключение индексации
	glutSwapBuffers(); // меняет фоновый буфер и буфер кадра местами
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv); // инициализируем библиотеку glut

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //опции включения двойной буферизации и буфера цвета

	glutInitWindowSize(1024, 768); // размер
	glutInitWindowPosition(100, 100); // позиция на экране
	glutCreateWindow("Tutorial 01"); // названия окна

	glutDisplayFunc(RenderSceneCB); // функция отображения на экран 

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // цвет окна


	GLenum res = glewInit(); // инициализация GLEW и проверка на ошибки
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}


	glm::vec3 Vertices[3]; // инициализация точек
	Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f); // XYZ
	Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
	Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);



	glGenBuffers(1, &VBO); // создание буфера для помещения объектов

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // связываем указатель к названию цели и затем запускаем команду на цель

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); // наполняем данными (буффер массива вершин, размер, массив, статически)

	glutMainLoop(); // передача контроля GLUT'у, чтобы дать ей возможность нарисовать кадр

}