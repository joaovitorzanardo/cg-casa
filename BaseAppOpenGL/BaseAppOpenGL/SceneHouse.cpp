#include "SceneHouse.h"

CSceneHouse::CSceneHouse()
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

}


CSceneHouse::~CSceneHouse(void)
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

double calcularAlturaInicial(double alturaObjAnterior, double alturaObjNovo) {
	return alturaObjAnterior + alturaObjNovo / 2;
}

void setCorObjeto(int r, int g, int b) {
	glColor4ub(r, g, b, 255);
}

void inserirPiso(double comprimento, double altura, double largura) {
	glPushMatrix();
	glTranslatef(0.0f, calcularAlturaInicial(0.0f, altura), 0.0);
	auxSolidBox(comprimento, altura, largura);
	glPopMatrix();
}

void inserirPilares(double alturaPiso, double  comprimentoCasa, double  alturaCasa, double  larguraCasa) {
	double alturaInicialPilar = calcularAlturaInicial(alturaPiso, alturaCasa);
	double xPilar = comprimentoCasa / 2 + 2;
	double yPilar = larguraCasa / 2 + 2;
	
	glPushMatrix();
	glTranslatef(-xPilar, alturaInicialPilar, -yPilar);
	auxSolidBox(1.0f, alturaCasa, 1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-xPilar, alturaInicialPilar, yPilar);
	auxSolidBox(1.0f, alturaCasa, 1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(xPilar, alturaInicialPilar, -yPilar);
	auxSolidBox(1.0f, alturaCasa, 1.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(xPilar, alturaInicialPilar, yPilar);
	auxSolidBox(1.0f, alturaCasa, 1.0f);
	glPopMatrix();
	
}

void inserirTelhado(double comprimentoCasa, double alturaCasa, double larguraCasa) {
	double comprimentoTelhado = comprimentoCasa / 2 + 4;
	double alturaTelhado = alturaCasa;
	double larguraTelhado = larguraCasa / 2 + 4;

	glColor4ub(0, 128, 0, 255);
	glBegin(GL_QUADS);
	glVertex3f(-comprimentoTelhado, alturaTelhado, larguraTelhado);
	glVertex3f(comprimentoTelhado, alturaTelhado, larguraTelhado);
	glVertex3f(comprimentoTelhado, alturaTelhado, -larguraTelhado);
	glVertex3f(-comprimentoTelhado, alturaTelhado, -larguraTelhado);
	glEnd();

	glColor4ub(0, 100, 0, 255);
	glBegin(GL_TRIANGLES);
	glVertex3f(-comprimentoTelhado, alturaTelhado, -larguraTelhado);
	glVertex3f(-comprimentoTelhado, alturaTelhado + 5.0f, 0.0f);
	glVertex3f(-comprimentoTelhado, alturaTelhado, larguraTelhado);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(comprimentoTelhado, alturaTelhado, -larguraTelhado);
	glVertex3f(comprimentoTelhado, alturaTelhado + 5.0f, 0.0f);
	glVertex3f(comprimentoTelhado, alturaTelhado, larguraTelhado);
	glEnd();

	glColor4ub(240, 128, 128, 255);
	glBegin(GL_QUADS);
	glVertex3f(-comprimentoTelhado, alturaTelhado, larguraTelhado);
	glVertex3f(-comprimentoTelhado, alturaTelhado + 5.0f, 0.0f);
	glVertex3f(comprimentoTelhado, alturaTelhado + 5.0f, 0.0f);
	glVertex3f(comprimentoTelhado, alturaTelhado, larguraTelhado);
	glEnd();

	glColor4ub(240, 128, 128, 255);
	glBegin(GL_QUADS);
	glVertex3f(-comprimentoTelhado, alturaTelhado, -larguraTelhado);
	glVertex3f(-comprimentoTelhado, alturaTelhado + 5.0f, 0.0f);
	glVertex3f(comprimentoTelhado, alturaTelhado + 5.0f, 0.0f);
	glVertex3f(comprimentoTelhado, alturaTelhado, -larguraTelhado);
	glEnd();
	
}

void inserirPorta(double alturaPiso, double larguraCasa) {
	glColor4ub(240, 128, 128, 255);
	glBegin(GL_QUADS);
	glVertex3f(-2.0f, alturaPiso, larguraCasa / 2 + 0.1);
	glVertex3f(-2.0f, alturaPiso + 8.0f, larguraCasa / 2 + 0.1);
	glVertex3f(2.0f, alturaPiso + 8.0f, larguraCasa / 2 + 0.1);
	glVertex3f(2.0f, alturaPiso, larguraCasa / 2 + 0.1);
	glEnd();

	glColor4ub(0, 0, 0, 255);
	glBegin(GL_QUADS);
	glVertex3f(1.0f, alturaPiso + 4.0f, larguraCasa / 2 + 0.2);
	glVertex3f(1.0f, alturaPiso + 4.5f, larguraCasa / 2 + 0.2);
	glVertex3f(1.5f, alturaPiso + 4.5f, larguraCasa / 2 + 0.2);
	glVertex3f(1.5f, alturaPiso + 4.0f, larguraCasa / 2 + 0.2);
	glEnd();
}

void inserirJanelas(double alturaPiso, double larguraCasa) {
	glColor4ub(209, 235, 247, 255);
	glBegin(GL_QUADS);
	glVertex3f(-8.0f, alturaPiso + 4.0f, larguraCasa / 2 + 0.1);
	glVertex3f(-8.0f, alturaPiso + 8.0f, larguraCasa / 2 + 0.1);
	glVertex3f(-4.0f, alturaPiso + 8.0f, larguraCasa / 2 + 0.1);
	glVertex3f(-4.0f, alturaPiso + 4.0f, larguraCasa / 2 + 0.1);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(4.0f, alturaPiso + 8.0f, larguraCasa / 2 + 0.1);
	glVertex3f(4.0f, alturaPiso + 4.0f, larguraCasa / 2 + 0.1);
	glVertex3f(8.0f, alturaPiso + 4.0f, larguraCasa / 2 + 0.1);
	glVertex3f(8.0f, alturaPiso + 8.0f, larguraCasa / 2 + 0.1);
	glEnd();
}

void inserirCasa(double alturaPiso, double comprimento, double altura, double largura) {
	glPushMatrix();
	glTranslatef(0.0f, calcularAlturaInicial(alturaPiso, altura), 0.0);
	auxSolidBox(comprimento, altura, largura);
	glPopMatrix();

	setCorObjeto(247, 243, 243);

	inserirPilares(alturaPiso, comprimento, altura, largura);
	inserirTelhado(comprimento, alturaPiso + altura, largura);
	inserirPorta(alturaPiso, largura);
	inserirJanelas(alturaPiso, largura);
}

void inserirDegrau(double altura, double largura) {
	glPushMatrix();
	glTranslatef(0.0f, calcularAlturaInicial(0.0f, altura / 2), (largura / 2) + 1);
	auxSolidBox(4.0f, altura , 2.0f);
	glPopMatrix();
}

int CSceneHouse::DrawGLScene(void)	// Fun��o que desenha a cena
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
	
	int alturaPiso = 2.0f;

	// CINZA
	setCorObjeto(192, 192, 192);

	inserirPiso(40.0f, alturaPiso, 30.0f);

	// CINZA ESCURO
	setCorObjeto(90, 90, 91);

	inserirDegrau(alturaPiso / 2, 30.f);

	// MARROM
	setCorObjeto(111, 78, 55);

	inserirCasa(alturaPiso, 20.0f, 10.0f, 10.0f);

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




void CSceneHouse::MouseMove(void) // Tratamento de movimento do mouse
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

void CSceneHouse::KeyPressed(void) // Tratamento de teclas pressionadas
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



}

void CSceneHouse::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
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
void CSceneHouse::Draw3DSGrid(float width, float length)
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



void CSceneHouse::DrawAxis()
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


