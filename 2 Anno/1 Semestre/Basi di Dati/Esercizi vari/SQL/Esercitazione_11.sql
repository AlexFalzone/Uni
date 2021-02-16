EVENTO(ide, titolo, data, idcateg, costo_partecipazione, idcate)
ORGANIZZATORE(ido,ide)
PERSONA(idp, nome, cognome, provincia_residenza)
PARTECIPANTE(ide,idp)
CATERING(idcate,nome,descrizione)
CATEGORIAEVENTO(idcateg,descrizione)

1.Trovare nome e cognome dei partecipanti agli eventi tenuti tra il 15 e il 20 dicembre 2013

SELECT nome, cognome
FROM Persona NATURAL JOIN  Partecipante NATURAL JOIN Evento
WHERE Evento.data BETWEEN 2013/12/15 AND 2013/12/20;

2.Trovare la persona che ha partecipato a tutti gli eventi di tipo “Festa Laurea”.

SELECT p.nome, p.cognome
FROM persona p
WHERE NOT EXISTS( 
                SELECT * 
                FROM categoriaevento ce NATURAL JOIN Evento e 
                WHERE ce.descrizione = "Festa Laurea"
                AND   NOT EXISTS(
                                SELECT *
                                FROM Partecipante pa
                                WHERE pa.ide = e.ide
                                AND   pa.idp = p.idp
                                )
                );


3.Trovare le persone che hanno partecipato a tutte le categorie di eventi.

CREATE VIEW PC AS
SELECT DISTINCT p.idp, e.idcateg
FROM partecipante p, evento e 
WHERE p.ide = e.ide;

SELECT nome, cognome
FROM persona p
WHERE NOT EXISTS( 
                SELECT *
                FROM categoriaevento ce
                WHERE NOT EXISTS(
                                SELECT *
                                FROM PC 
                                WHERE pc.idp = p.idp
                                AND   pc.idcateg = ce.idcateg 

                                )
                );


4.Trovare le persone che non hanno mai organizzato un evento di tipo “Matrimonio”

CREATE VIEW matrimoni AS
    SELECT persona.idp
    FROM evento NATURAL JOIN organizzatore JOIN persona ON organizzatore.ido = persona.idp, categoriaevento
    WHERE evento.ide = categoriaevento.ide 
    AND   categoriaevento.descrizione = "Matrimonio"

SELECT nome, cognome
FROM persona p
WHERE NOT EXISTS(
                SELECT *
                FROM matrimoni m
                WHERE p.idp = m.idp
                );



5.trovare l’outdegree medio dei nodi nel grafo

SELECT (sum(R.outDegree) + 0.0) / ( SELECT count(*)
                                    FROM( SELECT DISTINCT n1
                                          FROM arco
                                        UNION
                                          SELECT DISTINCT n2
                                          FROM arco 
                                        )
                                  )
FROM (SELECT n1, count(*) AS outDegree
      FROM arco
      GROUP BY n1
    ) AS R; 
