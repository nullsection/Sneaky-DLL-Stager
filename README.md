# Mischief-DLL-Stager
Moderately stealthy shellcode stager. 


```
                                    ******,,,******                             
                               .***    ......      .**,                         
                             **,   ...........         **                       
                           **  ,.............            **                     
                         **  (...............           . .**                   
,                      ,*, *(..................          (  **             .    
       ***********,,,,**  (*................              *  **              **,
    .******,      .,***  (,............                    *  *********.        
   ******           **  (,....(...                          ( .*. .******       
******.            *,  (/..(,..                              , **    *******,   
****              ,*. /(/(..                                 ( .*.      ********
**,               **  ((..                                   (  *,        ******
**              ,*,  (/..                                    .  **        .*****
       .       ,*.  (..       .@&...                         (/ ,*. .      *****
      *       .*.  (..         ..&@@@&.         .....#@.      (  ,*  *          
    *         **  (..             ....        .@@@@@%.         (  **  **        
   *.        ,*  /(..                                          (  ,*    ,*      
   *         **  ((..       *                                   ,  **    ,      
  .          **  /(..       .*                       .,        .   **    .      
        ,*****,   /(..        *                     *          (  ,*            
   ***,     /((...   (,.       .                  *.         /(  ,***.          
**.    (((...........    *                                 (,  ,,     ,***  ****
   (((,.................                               .    .......((/    ,*****
(((........................ ..                          ..............,((*   .**
*............................... ..               ........................((/   
........................................       .............................((( 
....... ... .............  ................. .............. ................../(
......... .  ..............     ........................ ......................(
..........   ..................  .................... ................  ........
...........   .......................................................   ........
............    ....................................................   .........

```

</br>
This is a very simple shellcode stager that as of right now moderately undetected. I chose to legitimately load functions and then dynamically load others 
to be less immedialtely suspicious. 
</br>

## Instrutions 
1. Simply generate your own shellcode using msfvenom, donut, powershellempire etc. 
2. Insert your routable ip within the cpp file <INSERT WEB IP HERE>. You can also change the function name exported too optionally. 
3. Compile the DLL 
4. Server your shellcode on your webserver
5. runddl32.exe stager.dll,update 

## Detections as of 04/2023
![image](https://user-images.githubusercontent.com/46195001/233060794-327b918c-e0f3-42f2-8a57-7b4106d683c5.png)


