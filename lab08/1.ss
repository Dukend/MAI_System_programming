;zeller.ss
(define (day-of-week)
 (zeller dd
      (cond((< mm 3)(+ mm 10))(#t (- mm 2)))
      (remainder (cond((< mm 3)(- yyyy 1)) (#t yyyy)) 100)
      (quotient (cond((< mm 3)(- yyyy 1)) (#t yyyy)) 100)
 )
)
(define (zeller d m y c)
 (neg-to-pos (remainder (+ d y
                          (quotient (-(* 26 m)2) 10)
                          (quotient y 4)
                          (quotient c 4)
                          (* 2(- c))
                       )
            7)
 )
)
(define (neg-to-pos d)
 (cond((< d 0)(+ d 7))
      (#t d)
 )
)
(define (birthday dw)
;                  ^{0,...,6}
 (display "Your were born on ")
 (display
     (if(= dw 1)"Monday "
     (if(= dw 2)"Tuesday "
     (if(= dw 3)"Wednesday "
     (if(= dw 4)"Thursday "
     (if(= dw 5)"Friday "
     (if(= dw 6)"Saturday "
     "Sunday " )))))))
  (display dd)(display ".")
  (display mm)(display ".")
 yyyy
)
(define dd 4)
(define mm 6)
(define yyyy 2001)
(birthday (day-of-week))