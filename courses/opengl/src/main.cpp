#include <windows.h>
#include <gl/glut.h>
#include "main.h"

int iShape = 1;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };



GLShapes::GLShapes()
{

}

void GLShapes::OnMenu( int value )
{
    iShape = value;
	glutPostRedisplay();
}

void GLShapes::OnRender( void )
{
	// 清空窗口
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// 保存矩阵与进行旋转
	glPushMatrix();

	glRotatef( xRot, 1.0f, 0.0f, 0.0f );
	glRotatef( yRot, 0.0f, 1.0f, 0.0f );
	
	// 重新绘制图形
	glColor3ub( 128, 128, 128 );
	switch( iShape )
	{
    case SPHERE:
        glutSolidSphere( 1.0f, 50, 50 );
        break;
	case CUBE:
        glutSolidCube( 1.0f );
        break;
	case CONE:
        glutSolidCone( 0.30, 1.1f, 30, 25 );
        break;
	case TORUS:
        glutSolidTorus( 0.3f, 1.0f, 25, 50 );
        break;
	case DODECAHEDRON:
        glutSolidDodecahedron();
        break;
	case OCTAHEDRON:
        glutSolidOctahedron();
        break;
	case TETRAHEDRON:
        glutSolidTetrahedron();
        break;
	case ICOSAHEDRON:
        glutSolidIcosahedron();
        break;
    case TEAPOT:    
		glutSolidTeapot( 1.0f );
        break;
	default:
		break;
    }

	glPopMatrix();
	glutSwapBuffers();

}



void GLShapes::SetupRC()
{
	//设置窗口背景色
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glEnable( GL_DEPTH_TEST );
	// 开启光照
	glEnable( GL_LIGHTING );

	// 开启并设置光源
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight ); // 环境泛光
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight ); // 漫反射
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );    // 镜面反射
	glEnable( GL_LIGHT0 );
	
	// 开启并设置材质
	glShadeModel( GL_FLAT ); // GL_SMOOTH
	glEnable( GL_COLOR_MATERIAL );
	
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	
	glMaterialfv( GL_FRONT, GL_SPECULAR, specref );
	glMateriali( GL_FRONT, GL_SHININESS, 128 );
}


void GLShapes::OnKeyDown( int key, int x, int y )
{
	// 处理旋转
	if ( key == GLUT_KEY_UP )
		xRot -= 5.0f;
	else if ( key == GLUT_KEY_DOWN )
		xRot += 5.0f;
	else if ( key == GLUT_KEY_LEFT )
		yRot -= 5.0f;
	else if ( key == GLUT_KEY_RIGHT )
		yRot += 5.0f;
	
	if ( key > 356.0f )			// 超过360度则置零
	{
		xRot = 0.0f;
		yRot = 0.0f;
	}
	else if ( key < -1.0f )	    // 小于-1度则置355
	{
		xRot = 355.0f;
		yRot = 355.0f;
	}
	
	/// 重绘
	glutPostRedisplay();
}


void GLShapes::OnResize( int w, int h )
{
	GLfloat	 lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };
	GLfloat nRange = 1.9f;

	if (h == 0) h = 1;

    glViewport( 0, 0, w, h );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 设置修剪空间的范围, 缩放
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glLightfv( GL_LIGHT0, GL_POSITION, lightPos ); // 重新设置光源
}

void GLShapes::SetupMenu()
{
	// 创建右键菜单
	int nMainMenu;
	nMainMenu = glutCreateMenu( OnMenu );

	// 添加子菜单
	glutAddMenuEntry( "Sphere", 1 ); 
	glutAddMenuEntry( "Cube", 2 );
	glutAddMenuEntry( "Cone", 3 );
	glutAddMenuEntry( "Torus", 4 );
	glutAddMenuEntry( "Dodecahedron", 5 );
	glutAddMenuEntry( "Octahedron", 6 );
	glutAddMenuEntry( "Tetrahedron", 7 );
	glutAddMenuEntry( "Icosahedron", 8 );
	glutAddMenuEntry( "Teapot", 9 );

	glutAttachMenu( GLUT_RIGHT_BUTTON );
}

void GLShapes::Start()
{
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutCreateWindow( "计算机图形学 opengl by jokerleee@gmail.com" );
	MessageBox( NULL, L"点击右键进行图形选择\n键盘的方向键对图形进行旋转", L"交互操作说明", MB_OK );
	
	SetupMenu();					// 设置右键菜单
	glutReshapeFunc( OnResize );	// 处理窗口大小变化
	glutSpecialFunc( OnKeyDown );	// 添加键盘交互
	glutDisplayFunc( OnRender );	// 设绘制回调函数
	SetupRC();						// 自定义的初始化例程

	glutMainLoop();					// 让GLUT框架开始运行, 处理交互事件
}

int main()
{
	/// 隐藏控制台
	FreeConsole();

	GLShapes app;
	app.Start();
	return 0;
}
