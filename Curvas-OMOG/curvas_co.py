import pygame
from pygame.locals import *
import numpy as np

### CORES ###
preto = (0, 0, 0)
azul_1 = (5,104,166)
azul_2 = (82, 242, 242)
verde_1 = (2, 81, 89)
verde_2 =(2, 115, 115)
branco = (225,225,225)
vermelho = (225,0,0)
vermelhoescuro = (128,0,0)
verde = (0,255,0)
verdeescuro = (0,128,0)

class ponto(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

def bspline(pontos_controle, nr_pontos_curva):
    n=len(pontos_controle)-1
    k=len(pontos_controle) #ordem 6, grau = ordem - 1
    x_ponto_controle = [p[0] for p in pontos_controle]
    y_ponto_controle = [p[1] for p in pontos_controle]

    knots=[0,0,0,0,1,1,1,1]
    t = np.linspace(0, 1, nr_pontos_curva)
    x_final=[0]*nr_pontos_curva
    y_final=[0]*nr_pontos_curva
    for j in range(0,len(t)):
        for i in range(0,len(pontos_controle)):
            aux=Boor(i,k,t[j],knots)
            x_final[j]=x_final[j] + (x_ponto_controle[i] * aux)
            y_final[j]=y_final[j] + (y_ponto_controle[i] * aux)
    return x_final,y_final

def Boor(i, k, t, knots):
    if k == 1:
        if(knots[i] <= t and t <= knots[i+1]):
            return 1.0
        else:
            return 0.0
    else:
        if(knots[i+k-1]-knots[i] == 0):
            aux1=0
        else:
            aux1=((t-knots[i])/(knots[i+k-1]-knots[i])) * Boor(i,k-1,t,knots)
        if(knots[i+k]-knots[i+1] == 0 ):
            aux2=0
        else:
            aux2=((knots[i+k]-t)/(knots[i+k]-knots[i+1])) * Boor(i+1,k-1,t,knots)
        return  aux1+aux2

def bezier(pontos_controle, nr_pontos_curva):
    n=len(pontos_controle)-1 #n eh o grau, ou seja, nr de pontos de controle - 1
    x_ponto_controle = [p[0] for p in pontos_controle]
    y_ponto_controle = [p[1] for p in pontos_controle]
    t = np.linspace(0, 1, nr_pontos_curva)
    x_final=[0]*nr_pontos_curva
    y_final=[0]*nr_pontos_curva
    for k in range(0,len(t)):
        for i in range(0,len(pontos_controle)):
            aux = binomio(i,n)*((1-t[k])**(n-i))*(t[k]**i)
            x_final[k]=x_final[k] + x_ponto_controle[i] * aux
            y_final[k]=y_final[k] + y_ponto_controle[i] * aux
    return x_final,y_final

def binomio(i,n):
    return fatorial(n)/(fatorial(i)*fatorial(n-i))

def fatorial(n):
    n_fat=1
    for i in range(2,n+1):
        n_fat = n_fat * i
    return n_fat

def callBspline(pontos_controle, nr_pontos_curva):
    pontosx, pontosy = bspline(pontos_controle, nr_pontos_curva)

    points = []

    for i in range (len(pontosx)):
        points.append((pontosx[i], pontosy[i]))

    return points

def callBezier(pontos_controle, nr_pontos_curva):
    pontosx, pontosy = bezier(pontos_controle, nr_pontos_curva)

    points = []

    for i in range (len(pontosx)):
        points.append((pontosx[i], pontosy[i]))

    return points

def main():
    pygame.init()
    tela = pygame.display.set_mode((1024, 1024))

    # Criando os pontos de controle da curva
    pontos_de_controle_bezier = [ponto(100,100), ponto(100,200), 
    ponto(100,300),ponto(100,400),ponto(100,500), ponto(100,600)]

    pontos_de_controle_spline = [ponto(600,100), ponto(600,200), 
    ponto(600,300),ponto(600,400)]

    pc_spline = []

    # Criando os textos
    smallfont = pygame.font.SysFont('Corbel',35)
    text = smallfont.render('Bezier 5' , True , branco)
    text2 = smallfont.render('B-Spline 3' , True , branco)
    text3 = smallfont.render('Limpar' , True , branco)
    text4 = smallfont.render('C0' , True , branco)
  
 
    # Inicializando variaveis
    selected = None
    BEZIER = False
    BSPLINE = False
    C0 = False
    aberto = True
    
    clock = pygame.time.Clock()
    

    while aberto:
        
        for event in pygame.event.get():
            if event.type in (QUIT, KEYDOWN):
                aberto = False
            elif event.type == MOUSEBUTTONDOWN and event.button == 1:
                for p in pontos_de_controle_bezier:
                    if abs(p.x - event.pos[0]) < 15 and abs(p.y - event.pos[1]) < 15 and BEZIER == False:
                        selected = p

                for p in pontos_de_controle_spline:
                    if abs(p.x - event.pos[0]) < 15 and abs(p.y - event.pos[1]) < 15 and BSPLINE == False:
                        selected = p

                if abs(100 - event.pos[0]) < 100 and abs(1000 - event.pos[1]) < 100:
                    BEZIER = True

                if abs(650 - event.pos[0]) < 100 and abs(1000 - event.pos[1]) < 100:
                    BSPLINE = True

                if abs(320 - event.pos[0]) < 100 and abs(1000 - event.pos[1]) < 100:
                    C0 = True

                if abs(950 - event.pos[0]) < 100 and abs(1000 - event.pos[1]) < 100:
                    BEZIER = False
                    BSPLINE = False
                    C0 = False


            elif event.type == MOUSEBUTTONUP and event.button == 1:
                selected = None

        tela.fill(branco)
        
        if selected is not None:
            selected.x, selected.y = pygame.mouse.get_pos()
            pygame.draw.circle(tela, azul_1, (selected.x, selected.y), 10)
       
        pygame.draw.rect(tela,verde_2,[50,900,130,60])
        tela.blit(text,(60,912))

        pygame.draw.rect(tela,verde_2,[350,900,70,60])
        tela.blit(text4,(365,912))

        pygame.draw.rect(tela,verde_2,[600,900,145,60])
        tela.blit(text2,(605,912))

        pygame.draw.rect(tela,verde_2,[880,900,120,60])
        tela.blit(text3,(890,912))
        
        pontosBezier = []
        for p in pontos_de_controle_bezier:
            aux = [p.x, p.y]
            pontosBezier.append(aux)
            pygame.draw.circle(surface = tela,color= verde,center= (int(p.x), int(p.y)),radius= 15)
        pc_bezier = pontosBezier

        pygame.draw.lines(tela, verde, False, [(x.x, x.y) for x in pontos_de_controle_bezier], width=3) 
        

        pontosSpline = []
        for p in pontos_de_controle_spline:
            aux = [p.x, p.y]
            pontosSpline.append(aux)
            pygame.draw.circle(surface = tela,color= vermelho,center= (int(p.x), int(p.y)),radius= 15)
        pc_spline = pontosSpline

        pygame.draw.lines(tela, vermelho, False, [(x.x, x.y) for x in pontos_de_controle_spline], width=3)

        # Curva de Bezier 4
        if BEZIER == True:
            print("Desenhando bezier")
            bezier_points = callBezier(pc_bezier, 1000)
            pygame.draw.lines(tela, pygame.Color(verdeescuro), False, bezier_points, 3)

        if BSPLINE == True:
            print("Desenhando bspline")
            
            bspline_points = callBspline(pc_spline, 1000)
            pygame.draw.lines(tela, pygame.Color(vermelhoescuro), False, bspline_points, 3)

        if C0 == True:
            ultimoPontoSpline = pontos_de_controle_spline[3]
            ultimox = ultimoPontoSpline.x
            ultimoy = ultimoPontoSpline.y

            deslocamento_x = pontos_de_controle_bezier[0].x - ultimox
            deslocamento_y = pontos_de_controle_bezier[0].y - ultimoy

            print(deslocamento_x)
            print(deslocamento_y)


            # exit()

            # pontos_de_controle_bezier = [ponto(100,100), ponto(100,200), 
            # ponto(100,300),ponto(100,400),ponto(100,500), ponto(100,600)]

            # pontos_de_controle_spline = [ponto(600,100), ponto(600,200), 
            # ponto(600,300),ponto(600,400)]


            newpcbezier = [
                ponto(ultimox,ultimoy),
                ponto(pontos_de_controle_bezier[1].x - deslocamento_x, pontos_de_controle_bezier[1].y - deslocamento_y),
                ponto(pontos_de_controle_bezier[2].x - deslocamento_x, pontos_de_controle_bezier[2].y - deslocamento_y),
                ponto(pontos_de_controle_bezier[3].x - deslocamento_x, pontos_de_controle_bezier[3].y - deslocamento_y),
                ponto(pontos_de_controle_bezier[4].x - deslocamento_x, pontos_de_controle_bezier[4].y - deslocamento_y),
                ponto(pontos_de_controle_bezier[5].x - deslocamento_x, pontos_de_controle_bezier[5].y - deslocamento_y)
                ]

            pontos_de_controle_bezier = newpcbezier


        pygame.display.flip()
        clock.tick(100)


if __name__ == '__main__':
    main()