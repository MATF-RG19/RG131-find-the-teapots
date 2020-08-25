# RG131-find-the-teapots
Find the Teapots je interaktivni program koji pokazuje neke osnovne mogucnosti OpenGL-a.
Pri pokretanju, na ekranu je soba. Cilj je da se u sobi pojave svi cajnici tako sto ce se uneti odgovarajuci kodovi na tastaturi. 
Kodovi su "tea", "pot" i "418". Zicani cajnik ce se pojaviti kada se pojave svi ostali cajnici. Cajnici se mogu resetovati klikom na dugme 'r'.

# Pokretanje
Program se downloaduje komandom "git clone https://github.com/MATF-RG19/RG131-find-the-teapots".
Nakon downloadovanja, program se pokrece tako sto se otvori folder projekta u terminalu, prevede se izvorni kod komandom "make", a potom se pokrene program sa "./findtheteapots".

# Koriscene biblioteke
Koriscene su biblioteke: 
GL/glut.h, koja moze da se instalira sa "sudo apt-get install freeglut3-dev" na Ubuntu sistemima, kao i sa "sudo yum install freeglut-devel" na Fedora sistemima