#include "Scene3.h"

CScene3::CScene3()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	
	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impress�o de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	//pTextures = new CTexture();	

	fAngle = 0.0f;
	fX = 0.0f;
	fY = 0.0f;
	fZ = 0.0f;
	fScale = 1.0f;
}


CScene3::~CScene3(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}	
}




int CScene3::DrawGLScene(void)	// Fun��o que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter
	
	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posi��es da c�mera
	pCamera->setView();

	// Desenha grid 
	Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espa�o)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (IN�CIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fAngle += 1.0f;
	if (fAngle >= 360.0f)
		fAngle = 0.0f;


	glPushMatrix();
	glTranslatef(fX, fY, fZ);
	glRotatef(fAngle, 0.0f, 1.0f, 0.0f);
	glScalef(fScale, fScale, fScale);

	glBegin(GL_QUADS);
	// Face da frente
	glColor4ub(255, 0, 0, 255);
	glVertex3f(-5.0f, -5.0, 5.0f);
	glVertex3f( 5.0f, -5.0, 5.0f);
	glVertex3f( 5.0f,  5.0, 5.0f);
	glVertex3f(-5.0f,  5.0, 5.0f);

	// Face de tras
	glColor4ub(255, 255, 0, 255);
	glVertex3f(-5.0f, -5.0, -5.0f);
	glVertex3f( 5.0f, -5.0, -5.0f);
	glVertex3f( 5.0f,  5.0, -5.0f);
	glVertex3f(-5.0f,  5.0, -5.0f);

	// Face da direita
	glColor4ub(0, 255, 0, 255);
	glVertex3f(5.0f, -5.0,  5.0f);
	glVertex3f(5.0f, -5.0, -5.0f);
	glVertex3f(5.0f,  5.0, -5.0f);
	glVertex3f(5.0f,  5.0,  5.0f);

	// Face da esquerda
	glColor4ub(0, 0, 255, 255);
	glVertex3f(-5.0f, -5.0, 5.0f);
	glVertex3f(-5.0f, -5.0, -5.0f);
	glVertex3f(-5.0f, 5.0, -5.0f);
	glVertex3f(-5.0f, 5.0, 5.0f);
	glEnd();


	glBegin(GL_TRIANGLES);
	// Face frente
	glColor4ub(130, 210, 199, 255);
	glVertex3f(-5.0f, 5.0f, 5.0f);
	glVertex3f( 5.0f, 5.0f, 5.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	// Face tras
	glColor4ub(130, 50, 50, 255);
	glVertex3f(-5.0f, 5.0f, -5.0f);
	glVertex3f(5.0f, 5.0f, -5.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	// Face direita
	glColor4ub(50, 150, 230, 255);
	glVertex3f(5.0f, 5.0f, -5.0f);
	glVertex3f(5.0f, 5.0f, 5.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	// Face esquerda
	glColor4ub(50, 210, 25, 255);
	glVertex3f(-5.0f, 5.0f, -5.0f);
	glVertex3f(-5.0f, 5.0f, 5.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();

	glPopMatrix();




	// Desenha um Teapot
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, 0.0);
	auxSolidTeapot(1.0);
	glPopMatrix();

	// Desenha um Cone
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 10.0);
	glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
	auxSolidCone(1.0, 3.0);
	glPopMatrix();

	// Desenha uma esfera
	glPushMatrix();
	glTranslatef(0.0f, 10.0f, 10.0);
	auxSolidSphere(2.0);
	glPopMatrix();


	



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impress�o de texto na tela...
	// Muda para modo de proje��o ortogonal 2D
	// OBS: Desabilite Texturas e Ilumina��o antes de entrar nesse modo de proje��o
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posi��o do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplica��o e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));


	glPopMatrix();

	// Muda para modo de proje��o perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene3::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os c�lculos de rota��o da vis�o do Player (atrav�s das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a c�mera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene3::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Sen�o, interrompe movimento do Player
	else
	{
	}

	if (GetKeyState(VK_UP) & 0x80)
	{
		fZ -= 1.0f;
	}
	if (GetKeyState(VK_DOWN) & 0x80)
	{
		fZ += 1.0f;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		fX += 1.0f;
	}
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		fX -= 1.0f;
	}
	if (GetKeyState(VK_PRIOR) & 0x80)
	{
		fY += 1.0f;
	}
	if (GetKeyState(VK_NEXT) & 0x80)
	{
		fY -= 1.0f;
	}

	if (GetKeyState(VK_ADD) & 0x80)
	{
		fScale += 0.01f;
	}
	if (GetKeyState(VK_SUBTRACT) & 0x80)
	{
		fScale -= 0.01f;
		if (fScale <= 0.01f)
			fScale = 0.01f;
	}



}

void CScene3::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene3::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void CScene3::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


