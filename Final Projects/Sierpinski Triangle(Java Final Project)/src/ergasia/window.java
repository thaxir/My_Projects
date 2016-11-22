/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ergasia;
import java.awt.Graphics;
import java.util.Random;
import javax.swing.JFrame;

/**
 * sxhmatizei to para8yro. trexei ton algori8mo kai sxhmatizetai to fractal
 * me vash auton.
 *
 * 
 * @author Thanos X!
 */
public class window extends JFrame{
   
    private static final int FRAMEWIDTH=800;
    private static final int FRAMEHEIGHT=600;
     Point B= new Point(400,50);//panw gwnia
     Point A= new Point(50,550);//katw aristera gwnia
     Point C= new Point(750,550);//katw deksia gwnia
     Point TrexonShmeio,ShmeioProorismou,EndiamesoShmeio;
    private int randomNumber,randomNumber2;
     Random generator = new Random();
     
     
     
     /**
      *Constructor ths klashs window, dhmiourgei to para8yro
      * arxikopoiwntas ta mege8h tou
      */

     
    public window() {
        
    super();
    setSize(FRAMEWIDTH,FRAMEHEIGHT);
    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setTitle("PROJECT 2012");

 
}
    
    @Override
    /**
     * zwgrafizei to fractal me vash ton algori8mo.Epilegei tyxaia 2 shmeia 
     * kai zwgrafizei sto endiameso tous ena pixel. Auto epanalamvanomeno
     * dhmiourgei to fractal
     * @param g 
     */
    public void paint(Graphics g){
     
        randomNumber=generator.nextInt(3);
    switch(randomNumber){
        case 0: TrexonShmeio=new Point(A.x,A.y);
        break;
        case 1: TrexonShmeio=new Point(B.x,B.y);
        break;
        case 2: TrexonShmeio=new Point(C.x,C.y);
        break;    
    
    }
    
    
    for(int i=0; i<100000;i++){
     randomNumber2=generator.nextInt(3);
    switch(randomNumber2){
        case 0: ShmeioProorismou= new Point(A.x,A.y);break;
        case 1: ShmeioProorismou=new Point(B.x,B.y);break;
        case 2: ShmeioProorismou=new Point(C.x,C.y);break;    
    
    }
    EndiamesoShmeio=new Point((TrexonShmeio.x+ShmeioProorismou.x)/2,(TrexonShmeio.y+ShmeioProorismou.y)/2);
        
        g.drawLine(EndiamesoShmeio.x,EndiamesoShmeio.y,EndiamesoShmeio.x,EndiamesoShmeio.y);
        TrexonShmeio=EndiamesoShmeio;
    }
    }
    
}
