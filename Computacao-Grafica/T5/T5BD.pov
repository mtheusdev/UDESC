#include "colors.inc"

camera {
    location <-15, 10, 15>
    look_at <0, 5, 0>
} 


light_source{
    <-1,6,-10>
    White
}        


background {Grey}

box{
    <0,0,0>, <5,10,5>
    pigment {Red}
    rotate <0,0, 0>
}


polygon {
    4,
   <0.0, 0.0, 0.0>,
   <0.0, 10, 0.0>,
   <5, 10, 0.0>,
   <5, 0.0, 0.0>
   
   pigment { 
    image_map {
        png "frente.png"
    }
    scale 5
   } 
    
}

polygon {
    4,
   <0.0, 0.0, 5>,
   <0.0, 10, 5>,
   <0.0, 10, 0.0>,
   <0.0, 0.0, 0.0>
   //<5, 0.0, 0.0>,
   //<5, 0.0, 5>,
   //<5, 10, 5>,
   //<5, 10, 0.0>
   
   pigment { 
    image_map {
        png "l_esquerdo.png"
    }
    translate <5, 0,0>
    rotate 90
    scale 5
   } 
    
}

polygon {
    4,
   <5, 0.0, 0.0>,
   <5, 0.0, 5>,
   <5, 10, 5>,
   <5, 10, 0.0>
   
   pigment { 
    image_map {
        png "l_direito.png"
    }
    translate <5, 0,0>
    rotate 90
    scale 5
   } 
    
}
   

polygon {
    4,
   <5, 0.0, 5>,
   <0.0, 0.0, 5>,
   <0.0, 10, 5>,
   <5, 10, 5>
   		
   pigment { 
    image_map {
        png "fundo.png"
    }
    translate <5, 0,0>
    rotate 90
    scale 5
   } 
    
}
 
