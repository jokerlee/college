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
	// ��մ���
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// ��������������ת
	glPushMatrix();

	glRotatef( xRot, 1.0f, 0.0f, 0.0f );
	glRotatef( yRot, 0.0f, 1.0f, 0.0f );
	
	// ���»���ͼ��
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
	//���ô��ڱ���ɫ
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glEnable( GL_DEPTH_TEST );
	// ��������
	glEnable( GL_LIGHTING );

	// ���������ù�Դ
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight ); // ��������
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight ); // ������
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );    // ���淴��
	glEnable( GL_LIGHT0 );
	
	// ���������ò���
	glShadeModel( GL_FLAT ); // GL_SMOOTH
	glEnable( GL_COLOR_MATERIAL );
	
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	
	glMaterialfv( GL_FRONT, GL_SPECULAR, specref );
	glMateriali( GL_FRONT, GL_SHININESS, 128 );
}


void GLShapes::OnKeyDown( int key, int x, int y )
{
	// ������ת
	if ( key == GLUT_KEY_UP )
		xRot -= 5.0f;
	else if ( key == GLUT_KEY_DOWN )
		xRot += 5.0f;
	else if ( key == GLUT_KEY_LEFT )
		yRot -= 5.0f;
	else if ( key == GLUT_KEY_RIGHT )
		yRot += 5.0f;
	
	if ( key > 356.0f )			// ����360��������
	{
		xRot = 0.0f;
		yRot = 0.0f;
	}
	else if ( key < -1.0f )	    // С��-1������355
	{
		xRot = 355.0f;
		yRot = 355.0f;
	}
	
	/// �ػ�
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

	// �����޼��ռ�ķ�Χ, ����
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glLightfv( GL_LIGHT0, GL_POSITION, lightPos ); // �������ù�Դ
}

void GLShapes::SetupMenu()
{
	// �����Ҽ��˵�
	int nMainMenu;
	nMainMenu = glutCreateMenu( OnMenu );

	// ����Ӳ˵�
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
	glutCreateWindow( "�����ͼ��ѧ opengl by jokerleee@gmail.com" );
	MessageBox( NULL, L"����Ҽ�����ͼ��ѡ��\n���̵ķ������ͼ�ν�����ת", L"��������˵��", MB_OK );
	
	SetupMenu();					// �����Ҽ��˵�
	glutReshapeFunc( OnResize );	// �����ڴ�С�仯
	glutSpecialFunc( OnKeyDown );	// ��Ӽ��̽���
	glutDisplayFunc( OnRender );	// ����ƻص�����
	SetupRC();						// �Զ���ĳ�ʼ������

	glutMainLoop();					// ��GLUT��ܿ�ʼ����, �������¼�
}

int main()
{
	/// ���ؿ���̨
	FreeConsole();

	GLShapes app;
	app.Start();
	return 0;
}
