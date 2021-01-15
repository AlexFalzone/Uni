IMPIEGATO(matricola, nome, cognome, dipartimento)
DIPARTIMENTO(id, nome, sede)
BENEFIT(id,nome,valore)
GADGET(id,nome,tipo,valore)
BENEFITASSEGNATO(matricola,id,data)
GADGETASSEGNATO(matricola,id,data)

--Trovare i dipartimenti che hanno avuto gadget per un valore totale maggiore di quello medio di tutti i dipartimenti con sede ‘SICILIA’;

CREATE VIEW sicilia AS 
SELECT SUM(valore) media
FROM gadget g NATURAL JOIN gadgetAssegnato NATURAL JOIN impiegato JOIN dipartimento ON i.dipartimento = d.id
WHERE D.sede = "Sicilia"
GROUP BY id.dipartimento;

SELECT SUM(valore), i.dipartimento
FROM gadget g NATURAL JOIN gadgetAssegnato NATURAL JOIN impiegato i
GROUP BY i.dipartimento
HAVING SUM(valore) >= (SELECT AVG(media)
                       FROM sicilia;                      
                      );


--Trovare i dipendenti che hanno avuto tutti i tipi di gadget;

SELECT *
FROM impiegati i 
WHERE NOT EXISTS ( SELECT *
                   FROM gadget g
                   WHERE NOT EXISTS( SELECT *
                                     FROM gadget_assegnato ga
                                     WHERE ga.matricola = i.matricola 
                                     AND   ga.id = g.id 
                                   
                                   )

                 );

--Trovare i dipendenti che hanno avuto benefit e dipendenti che non hanno avuto benefit (scrivere solo una query piana);

SELECT nome, cognome
FROM dipendenti;


--Aggiungere l’attributo ‘valore totale’ alla relazione IMPIEGATO e scrivere un trigger che, all’assegnazione di un nuovo benefit o gadget, aggiorni tale attributo.

CREATE TRIGGER T1
AFTER INSERT ON benefitassegnato 
FOR EACH ROW 
UPDATE valore_totale ON impiegato
SET valore_totale = valore_totale + ( SELECT valore
                                      FROM benefit
                                      WHERE benefit.id = new.id 
                                    )
WHERE new.matricola = matricola;

ALTER TABLE impiegato 
ADD COLUMN valore_totale INTEGER;