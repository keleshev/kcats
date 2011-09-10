#lang racket


(define (push smth stack) (cons smth stack))


(define (kcats [s '()])
  (display s)
  (printf "\nkcats> ")
  (define in (read))
 ;(display in)
  (case in
    [(:q)  ":q!!"]
    [(:s)  (display s)]
    [else  (kcats (push in s))]))



(kcats)



