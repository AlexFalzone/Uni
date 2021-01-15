Escursione(id, titolo, descrizione, durata, difficoltà, costo)
DataEscursione(id, data, idescursione, idguida)
Partecipante(idpartecipante, idescursione)
Persona(id, nome, cognome)

1. Trovare le escursioni (indicando titolo, descrizione e difficoltà) che hanno un costo massimo

select escursione.id, escursione.titolo, escursione.descrizione, 
from escursione s1 
where not exist (select * 
		 from escursione s2
		 where s2.costo > s1.costo)




2.Trovare i partecipanti (dando nome e cognome in output) che hanno partecipato	a tutte le escursioni	

select * 
from persona 
where not exist (select *
		from escursione 
		where not exist (select *
				from partecipante
				where partecipante.id_partecipante = persona.id and
				      escursione.id = partecipante.id_escursione))


3.Trovare le guide che non hanno mai partecipato ad escursioni di difficoltà massima	

select p1.nome , p1.cognome , de.id_guida
from persona p1, data_escursione de
where p1.id = de.guida  and NOT EXIST ( select *
					from partecipante pa NATURAL JOIN escursione e
					where pa.id_partecipante = p1.id and 
						de.id_escursione = e.id and
						e.difficolta = ( select max(difficolta) from escursione)




4.Trovare le coppie di persone che hanno partecipato sempre alle stesse	escursioni

select distinct p1.id , p2.id
from partecipante p1, partecipante p2
where p1.ide = p2.ide AND p1.idp > p2.idp 
	AND NOT EXIST ( select * 
			from data_escurisone e 
			where e.ide <> p1.ide AND ( EXIST ( select * 
							    from partecipante p3
							    where p3.ide = e.id and 
								  p3.idp = p1.idp)
                                                    AND NOT EXIST ( select *
								    from partecipante p3
								    where p3.ide = e.id and
								          p3.idp = p2.idp))
			 OR ( EXIST ( select *
				     from partecipante p3
                                     where p3.ide = e.id and 
					   p3.idp = p2.idp)
                            AND NOT EXIST ( select * 
					    from partecipante p3
				            where p3.ide = e.id and
						  p3.idp = p1.idp))))
		  

   


5.Dire ogni accompagnatore quante escursioni ha	guidato

select g1.id_guida , count(*) "numero escursioni"
from data_escursione g1
gruop by g1.id_guida 




QUERY SUI GRAFI

ARCO(n1,n2).


1.Scrivere una query SQL per trovare il	nodo con il più	alto out-degree.

SELECT COUNT(*) "out"
FROM arco
GROUP BY n1
HAVING out >= ALL(SELECT COUNT(*)
		  FROM arco
		  GROUP BY n1);



2.Modificare la soluzione per 1 e trovare gli identificatori con il più alto “in-degree”.

SELECT COUNT(*) "in"
FROM arco
GROUP BY n2
HAVING in >= ALL(SELECT COUNT(*)
	         FROM arco
		 GROUP BY n2);

3.Scrivere una query per trovare un cammino che	va dal nodo X al nodo Y.

WITH RECURSIVE cammino(n1,n2) AS
     (SELECT n1,n2 
      FROM arco)

	UNION
 
     (SELECT arco.n1, cammino.n2
      FROM arco, cammino
      WHERE arco.n2 = cammino.n1)   
	
      SELECT *
      FROM cammino;











