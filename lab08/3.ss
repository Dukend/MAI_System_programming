;coin21.ss
(define VARIANT 13)
(define LAST-DIGIT-OF-GROUP-NUMBER 6)
(define KINDS-OF-COINS 6)

(define (first-denomination kind-of-coins)
  (cond ((= kind-of-coins 1) 1)
        ((= kind-of-coins 2) 2)
        ((= kind-of-coins 3) 3)
        ((= kind-of-coins 4) 5)
        ((= kind-of-coins 5) 10)
        ((= kind-of-coins 6) 20)
        (#t 0)
   )
)

(define (count-change amount)
   (display "______\n amount: ")
   (display amount)
   (newline)
   (display "KINDS-OF-COINS: ")
   (display KINDS-OF-COINS)
   (newline)
   (let((largest-coin (first-denomination KINDS-OF-COINS)))
     (display "largest-coin: ")
     (display largest-coin)
     (newline)
     (cond((and (< 0 amount) (< 0 KINDS-OF-COINS) (< 0 largest-coin))
          (display "List of coin denominations: ")
          (denomination-list KINDS-OF-COINS)
          (display "count-change= ")
          (cc amount KINDS-OF-COINS)
        )
        (#t(display "Improper parameter value!\ncount-change= ") -1))) 
)
(define (pier? x? y?)
  (= 0 (cond((or x? y?) 1)(#t 0)))
)

(define (cc amount kinds-of-coins)
  (cond ((= amount 0) 1)
        ((pier? (< amount 0) (= kinds-of-coins 0))
        (+ (cc amount (- kinds-of-coins 1)) 
		(cc (- amount (first-denomination kinds-of-coins)) kinds-of-coins))
        )
        (#t 0)
  )
)

(define (denomination-list  kinds-of-coins)
        (cond((= kinds-of-coins 0) (newline) 0)
             (#t (display(first-denomination kinds-of-coins))
                   (display" ")
                   (denomination-list (- kinds-of-coins 1)))
        )
)

(define (GR-AMOUNT)
  (remainder (+ (* 100 LAST-DIGIT-OF-GROUP-NUMBER) VARIANT) 231)
)

(display "Variant ")
(display VARIANT)
(newline)
(newline)
(display (count-change 100))
(newline)
(display (count-change (GR-AMOUNT)))
(newline)
(set! KINDS-OF-COINS 13)
(display (count-change 100))
(newline)
(display "(c) Kondratev E.A. 2021\n")