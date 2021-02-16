SequelDI(film,sequel)

1.Trovare le coppie (x,y) tali che y è sequel di x o il sequel del sequel ecc. Definiamo la relazione FollowON

WITH RECURSIVE FollowON(film, sequel) AS
SELECT film, sequel
FROM sequel 
    UNION
SELECT s.film, fo.sequel
FROM sequel s, followON fo
WHERE s.sequel = fo.film

SELECT * FROM followON fo
WHERE fo.film = "x";

2.Trovare i film x che hanno halmeno due FollowON (sequel e sequel del sequel)

WITH RECURSIVE FollowON(film, sequel) AS
SELECT film, sequel
FROM sequel 
    UNION
SELECT s.film, fo.sequel
FROM sequel s, followON fo
WHERE s.sequel = fo.film

SELECT COUNT(*) num
FROM follow ON fo
GROUP BY fo.film
HAVING num>2;

3.Trovare le coppie (x,y) tali che y è il FollowON e y ha al piu’ un solo FollowON

WITH RECURSIVE FollowON(film, sequel) AS
SELECT film, sequel
FROM sequel 
    UNION
SELECT s.film, fo.sequel
FROM sequel s, followON fo
WHERE s.sequel = fo.film

SELECT fo.film, fo.sequel
FROM followON fo
WHERE fo.film = "x" AND
      fo.film = "y" AND
      (1>= (SELECT COUNT(*)
            FROM followON fo2
            WHERE fo2.film = fo.sequel
           )
      );





MATERIE (Codice, Facoltà, Denominazione, Professore)
STUDENTI (Matricola, Cognome, Nome, Facoltà)
PROFESSORI (Matricola, Cognome, Nome)
ESAMI (Studente, Materia, Voto, Data)
PIANIDISTUDIO (Studente, Materia, Anno)


1.gli studenti che hanno riportato in almeno un esame una votazione pari a 30, mostrando , per ciascuno di essi, nome e cognome e data della prima di tali occasioni

SELECT s.nome, s.cognome, MIN(e.data)
FROM esami e JOIN studenti s ON s.matricola = e.studente
WHERE e.voto = 30
GROUP BY s.matricola;


2.per ogni insegnamento della facoltà di ingegneria, gli studenti che hanno superato l esame nell ultima seduta svolta;

SELECT e.matricola, m.denominazione
FROM esami e JOIN materie m ON m.codice = e.Materia
WHERE m.facolta = "ingegneria" 
AND   e. voto >= 18 
AND NOT EXISTS( SELECT *
                FROM esami e2
                WHERE e2.data > e.data 
                AND   e2.studente = e.studente
                AND   e2.materia = e.materia
              );


3.gli studenti che hanno superato  tutti gli esami previsti dal rispettivo piano di studio;

SELECT p.studente
FROM pianostudio p
WHERE NOT EXISTS (SELECT *
                  FROM materie m
                  WHERE NOT EXISTS (SELECT * 
                                    FROM esami e 
                                    WHERE e.voto >= 18
                                    AND   e.studente = p.studente
                                    AND   e.materia = m.codice 
                                   )  
                 );


4.per ogni insegnamento della facoltà di lettere, lo studente (o gli studenti) che hanno superato l esame con il voto più alto 

SELECT e.studenti
FROM esami e JOIN materie m ON e.materia = m.codice
WHERE m.facolta = "lettere"
AND NOT EXISTS( SELECT *
                FROM esami e2
                WHERE e1.studente = e2.studente
                AND   e1.voto < e2.voto
              );


5.gli studenti che hanno in piano di studio solo gli insegnamenti della propria facoltà;

SELECT s.matricola
FROM studenti s
WHERE NOT EXISTS( SELECT *
                  FROM pianostudio ps, materia m
                  WHERE ps.studente = s.matricola
                  AND   ps.materia = m.codice
                  AND   m.facolta <> s.facolta
                );


6.nome e cognome degli studenti che hanno sostenuto almeno un esame con un professore che ha il loro stesso nome proprio.

SELECT s.nome, s.cognome
FROM studenti s JOIN esami e ON s.matricola = e.studenti 
                JOIN materia m ON m.codice = e.materia 
                JOIN professori ON p.matricola = m.professore
WHERE s.nome = p.nome;
