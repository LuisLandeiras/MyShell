# MyShell
<p>MyShell is a simple shell used to recreate and understand how the comands of the shell from linux terminal work.</p>

## How to compile the shell?
<p>All you need to do is install makefile extensions and then write make in terminal. After that a file named soshell will be created and like every c program you do ./soshell to run the code. To clear de trash files just do make clean.</p>

## Commands available:
- aviso;
- bits;
- calc;
- exit;
- info;
- isjpeg;
- maior;
- version;
- remover;
- setx;
- PS1=;
- socp.

## Future features:
- mycat;
- pipes.

## Functions explanation:
### Calc.c:
<p>A feature that do simple math calculations and binary maths.</p>
<ul>
 <li>Example:
   <ul>
     <li>Input: calc 2 + 4</li>
     <li>Output: bits 6</li>
   </ul>
 </li>
 <li>Example(with bits):
  <ul>
   <li>Input: 2 & 3</li>
   <li>Output: 2</li>
  </ul>
 </li>
</ul>

### Maior.c
<p>Compare two files and gives the bigger one.</p>
<ul>
 <li>Example:
   <ul>
     <li>Input: maior file1(20Kb) file2(12Kb)</li>
     <li>Output: file1</li>
   </ul>
 </li>
</ul>

### Jpeg.c
<p>Verify if a file is jpeg or not.</p>
<ul>
  <li>Example:
    <ul>
      <li>Input: isjpeg img.jpeg</li>
      <li>Output: Is jpeg</li>
    </ul>
  </li>
</ul>

### Aviso.c
<p>Here you can put a costumized warning where you set the message and the time. When the time is up the message will show up in the shell. While the message is waiting to show up you can use the shell normally</p>
<ul>
  <li>Example:
    <ul>
      <li>Input: aviso hello 5</li>
      <li>*after 5 seconds*</li>
      <li>output: Aviso:hello</li>
    </ul>
  </li>
</ul>    

### Socp.c
<p>Function used to copy a file to another</p>





  
    
    


