class GLShapes
{

public:
	GLShapes();
	void Start();

private:
	void SetupRC();
	void SetupMenu();

// »Øµôº¯Êý
public:
	static void OnMenu( int value );
	static void OnRender( void );
	static void OnKeyDown( int key, int x, int y );
	static void OnResize( int width, int height );

public:
	enum shapt{ SPHERE=1, CUBE, CONE, TORUS, DODECAHEDRON, OCTAHEDRON, TETRAHEDRON, ICOSAHEDRON, TEAPOT };

private:	
	
};