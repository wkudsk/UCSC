#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/racket/bin/mzscheme -qr
;; $Id: sbi.scm,v 1.4 2018-04-11 16:31:36-07 - - $
;;
;; NAME
;;    sbi.scm - silly basic interpreter
;;
;; SYNOPSIS
;;    sbi.scm filename.sbir
;;
;; DESCRIPTION
;;    The file mentioned in argv[1] is read and assumed to be an SBIR
;;    program, which is the executed.  Currently it is only printed.
;;

(define *stdin* (current-input-port))
(define *stdout* (current-output-port))
(define *stderr* (current-error-port))

;;making label hash table
(define lblhash (make-hash))
;; making statement hash table 
(define stthash (make-hash))
;; making variable hash table
(define varhash (make-hash))

;;Commonly called functions
(define (get-label key)
    (hash-ref lblhash key `(no such key)))

(define (insert-label! key value)
    (hash-set! lblhash key value))

(define (get-statement key)
    (hash-ref stthash key `(no such key)))

(define (insert-statement! key value)
    (hash-set! stthash key value))

(define (get-variable key)
    (hash-ref varhash key `(no such key)))

(define (insert-variable! key value)
    (hash-set! varhash key value))

;;Evaluates expression and applies the right statement
(define (eval-expression line)
	(cond (pair? line)
    	(apply (get-statement (car line)) (map eval-expression (cdr line)))     
    ((number? line) line)               
  	(else (get-variable line))))

;; PRINT statement
(define (my-print str) 
   (if (not (null?  str) )
     (begin
          (if (string? (car str))  
            (display (car str))
            (display (eval-expression (car str)))      
          )         
          (my-print (cdr str))
      )
         (newline)))

;; INPUT Statement
(define (my-input expr)
  (insert-variable! 'inputcount 0)
  (define (get-input expr)
     (when (not (null? (car expr)))
        (insert-variable! (car expr) (void))
        (let ((object (read)))
      (cond [(eof-object? object)(insert-variable! 'inputcount -1)]
       [(number? object)(insert-variable! (car expr) object)
        (insert-variable! 'inputcount (+ (get-variable 'inputcount) 1))]
          [else (begin (printf "invalid number: ~a~n" object)
                                )] )) 
         (when (not (null? (cdr expr)))
     (get-input (cdr expr)))
   )
  )
  (get-input expr)
)

;; DIM Statement (Declare in Memory - used for creating arrays)
(define (my-dim expr)
  ;;insert into the variable table the pointer to the head of the array
  (insert-variable! (caar expr) (make-vector (eval-expression (cadar expr))) )
  ;;insert the variable into the statement table so that the you can look up values in the array
  (insert-statement! (caar expr) 
      (lambda(x) (vector-ref (get-variable (caar expr)) (- x 1)))))

;; LET Statement
(define (my-let expr)
  (if (pair? (car expr))
    (begin
     (vector-set! (get-variable (caar expr)) 
     (- (eval-expression (cadar expr)) 1) (eval-expression (cadr expr)))
    )
    (begin
     (let ((result (eval-expression (cadr expr))))
       (insert-variable! (car expr) result)
     ))))

;; GOTO Statement
(define (my-goto label program)
   (run-program program (get-label (car label))))


(for-each
	(lambda (pair) (insert-statement! (car pair) (cadr pair)))
	`(

	(log10_2 0.301029995663981195213738894724493026768189881)
	(sqrt_2 1.414213562373095048801688724209698078569671875)
	(e 2.718281828459045235360287471352662497757247093)
	(pi 3.141592653589793238462643383279502884197169399)
	(/ ,(lambda (x y) (floor (/ x y))))
	(log10 ,(lambda (x) (/ (log x) (log 10.0))))
	(% ,(lambda (x y) (- x (* (div x y) y))))
	(quot ,(lambda (x y) (truncate (/ x y))))
	(rem ,(lambda (x y) (- x (* (quot x y) y))))
	(+ ,+)
	(-, -)
	(*, *)
	(^ ,expt)
	(ceil ,ceiling)
	(exp ,exp)
	(floor ,floor)
	(abs , abs)
	(log ,log)
	(sqrt ,sqrt)
	(exp, exp)
	(sin, sin)
	(cos, cos)
	(tan, tan)
	(acos, acos)
	(asin, asin)
	(atan, atan)
	(round, round)
	(print, my-print)
	(let, my-let)
	(dim, my-dim)
	(goto, my-goto)
	(if, void)
	(input, my-input)
	))

;;Takes in the labels and puts them in the label table
(define (find-labels program) 
(when (not (null? program))
          (let ((linenumber (caar program)))
               (when (and (number? linenumber) (not (null? (cdr(car program)))) (symbol? (car(cdr(car program)))))
                  (insert-label! (car(cdr(car program))) (caar program))))
          (find-labels (cdr program))))

;;finds the statement from the statement hashtable and ap
(define (interpret-statement statement program linenumber)
	;;if there is not statement, then we can continue. This in theory should not be checked though.
	(if (null? statement)
		(run-program program (+ linenumber 1))
	(begin
		;;statement does not exist in the hashtable, then there is an error
		(when (not (hash-has-key? stthash (car statement )))
    		(display (car statement))(display " is not valid")(newline)
	    	(usage-exit))
		
		(cond
		((eqv? (car statement) 'goto)
	  		;;goto: (goto) (label)
	  		(display "here")
	  		(run-program program (- (get-label (cadr statement)) 1)))
		((eqv? (car statement) 'if)
	  		(display "over here")
	  		;;if statement: (if) (expression) (label)
	  		(if (equal? #t (eval-expression (cadr statement)))
	    		;;if true statement, jump to label
	    		(run-program program (- (get-label (caddr statement)) 1))
	  		;;otherwise continue to next line
	  		(run-program program (+ linenumber 1))))  
		(else
			(display "this is where I should be")
			;;most other statements are (statement) (parameters)
	  		((get-statement (car statement)) (cdr statement))
	  		;;no jump required with if not a goto or if statement, so just jump to next line.
	  		(run-program program (+ linenumber 1)))))))


;;runs the meat of the program, most of the work is done in here
(define (run-program program linenumber)
 ;;program terminates when at the last line, checks to make sure
 (when (< linenumber (length program))
          (let ((line (list-ref program linenumber)))
             (cond
             	;;if there is a label, skip it when looking at the function
             	((= (length line) 3) 
                 (set! line (cddr line))
                 (interpret-statement (car line) program linenumber)
               )
             	;;if there is not a label, just skip line number
               ((and (= (length line) 2) (list? (cadr line)))
               (set! line (cdr line))
               ;;(display (car line))
               ;;(display 'line)
               ;;Have to print the car of the line because its the actual element
               (interpret-statement (car line) program linenumber)
               )           
               (else
                  (run-program program (+ linenumber 1)))
             ))))





;;given code, not made by us
(define *run-file*
(let-values
    (((dirpath basepath root?)
        (split-path (find-system-path 'run-file))))
    (path->string basepath))
)

(define (die list)
(for-each (lambda (item) (display item *stderr*)) list)
(newline *stderr*)
(exit 1)
)

(define (usage-exit)
(die `("Usage: " ,*run-file* " filename"))
)

(define (readlist-from-inputfile filename)
(let ((inputfile (open-input-file filename)))
     (if (not (input-port? inputfile))
         (die `(,*run-file* ": " ,filename ": open failed"))
         (let ((program (read inputfile)))
              (close-input-port inputfile)
                     program))))
;; list program lists all the 
(define (write-program-by-line filename program)
(printf "==================================================~n")
(printf "~a: ~s~n" *run-file* filename)
(printf "==================================================~n")
(printf "(~n")
(map (lambda (line) (printf "~s~n" line)) program)
(printf ")~n"))
;;(printf (program))
;;(interpret-program program))



(define (main arglist)
(if (or (null? arglist) (not (null? (cdr arglist))))
    (usage-exit)
    (let* ((sbprogfile (car arglist))
           (program (readlist-from-inputfile sbprogfile)))
          ;;(write-program-by-line sbprogfile program)
          (find-labels program)
          (run-program program 0))))

(when (terminal-port? *stdin*)
	(main (vector->list (current-command-line-arguments))))
