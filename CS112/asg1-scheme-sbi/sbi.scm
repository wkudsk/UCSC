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
(define *label-table* (make-hash))
;; making statement hash table 
(define *identifier-table* (make-hash))
;; making symbol hash table
(define *symbol-table* (make-hash))

;;Commonly called functions
(define (label-ref key)
    (hash-ref *label-table* key `(no such key)))

(define (label-set! key value)
    (hash-set! *label-table* key (- value 1)))

(define (identifier-ref key)
    (hash-ref *identifier-table* key `(no such key)))

(define (identifier-set! key value)
    (hash-set! *identifier-table* key value))

(define (symbol-ref key)
    (hash-ref *symbol-table* key `(no such key)))

(define (symbol-set! key value)
    (hash-set! *symbol-table* key value))

;;Evaluates expression and applies the right statement
(define (eval-expression program-line)
  (if (pair? program-line)
    (apply (identifier-ref (car program-line)) (map eval-expression (cdr program-line)))     
    (if (number? program-line) 
            program-line               
            ;;(display (program-line) (newline))
            (symbol-ref program-line)
          
    )
  )
)


;; DIM Statement (Declare in Memory - used for creating arrays)
;;(dim (a 10))
(define (my-dim expr)
  ;;insert into the symbol table the pointer to the head of the array
  ;;https://docs.racket-lang.org/reference/vectors.html
  (symbol-set! (caar expr) (make-vector (eval-expression (cadar expr))) )
  ;;insert the symbol into the statement table so that the you can look up values in the array
  (identifier-set! (caar expr) 
      (lambda(x) (vector-ref (symbol-ref (caar expr)) (- x 1)))))

;; LET Statement
(define (my-let expr)
  ;;(let (a i) 9)
  ;;if the expression is for an array
  (if (pair? (car expr))
    (begin
     (vector-set! (symbol-ref (caar expr))
     ;;arrays are supposed to indexed at 0, but scheme indexes at 1
     (- (eval-expression (cadar expr)) 1) (eval-expression (cadr expr)))
    )
    ;;(let i 1)
      (symbol-set! (car expr) (eval-expression (cadr expr)))
  )
)

;;goto: (goto) (label)
(define (my-goto statement program)
   (run-program program (label-ref (cadr statement)))
)

(define (my-if program statement linenumber)
  ;;if statement: ((if) (expression) (label))
  (if (equal? #t (eval-expression (cadr statement)))
    ;;if true statement, jump to label
    ((identifier-ref 'goto) (cdr statement) program)
    ;;otherwise continue to next line
    (run-program program (+ linenumber 1))
  )
)

;; PRINT statement
(define (my-print str) 
 (if (null?  str)
   (newline)
   (begin
      (if (string? (car str))  
        (display (car str))
        (display (eval-expression (car str)))      
      )         
      (my-print (cdr str))
    )
  )
)

;; INPUT Statement
(define (my-input expr)
  (symbol-set! 'inputcount 0)
  ;;tail end recursion
  (define (get-input expr)
    (when (not (null? (car expr)))
      ;;(symbol-set! (car expr) (void))
      (let ((in (read)))
        ;;https://www.scheme.com/tspl3/io.html
        (cond
          ;;stop when -1 is entered
          ((and (number? in) (= in -1)) (symbol-set! 'inputcount -1))
          
          ;;if its a number, add it to symbol table
          ((number? in)(symbol-set! (car expr) in)
          (symbol-set! 'inputcount (+ (symbol-ref 'inputcount) 1)))
          
          ;;anything else is discarded
          (else (begin (printf "invalid number: ~a~n" in)))
        )
      ) 
      (when (not (null? (cdr expr)))
        (get-input (cdr expr))
      )
    )
  )
  (get-input expr)
)


(for-each
	(lambda (pair) (identifier-set! (car pair) (cadr pair)))
	`(

	(log10_2 0.301029995663981195213738894724493026768189881)
	(sqrt_2 1.414213562373095048801688724209698078569671875)
	(e 2.718281828459045235360287471352662497757247093)
	(pi 3.141592653589793238462643383279502884197169399)
  ;;if y is equal to 0, divide by a floating point zeros
	(/ ,(lambda (x y) (floor (/ x (if (equal? y 0) 0.0 y)))))
	;;
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
  ;;if x is equal to 0, divide by a floating point 0
	(log , (lambda (x) (log (if(equal? x 0) 0.0 x))))
	(sqrt ,sqrt)
	(exp, exp)
	(sin, sin)
	(cos, cos)
	(tan, tan)
	(acos, acos)
	(asin, asin)
	(atan, atan)
	(round, round)
	(dim, my-dim)
	(let, my-let)
	(goto, my-goto)
	(if, my-if)
  (print, my-print)
	(input, my-input)
  (<= ,(lambda (x y) (<= x y)))
  (>= ,(lambda (x y) (>= x y)))
  (< ,(lambda (x y) (< x y)))
  (> ,(lambda (x y) (> x y)))
  (= ,(lambda (x y) (eqv? x y)))
  (<> ,(lambda (x y) (not (equal? x y))))
	))

;;Takes in the labels and puts them in the label table
(define (find-labels program) 
  (when (not (null? program)) 
    (when (number? (caar program))
      (when (and (not (null? (cdar program))) (symbol? (cadar program)))
        (label-set! (cadar program) (caar program))
      )
    )
    (find-labels (cdr program))
  )
)

;;finds the statement from the statement hashtable and ap
(define (interpret-statement statement program linenumber)
	;;if there is not statement, then we can continue. This in theory should not be checked though.
	(if (null? statement)
		(run-program program (+ linenumber 1))
	(begin
		;;statement does not exist in the hashtable, then there is an error
		(when (not (hash-has-key? *identifier-table* (car statement )))
    		(display (car statement))(display " is not valid")(newline)
	    	(usage-exit))
		(cond
		((eqv? (car statement) 'goto)
	  		((identifier-ref 'goto) statement program))
		((eqv? (car statement) 'if)
	  		;;(display "over here")
        ((identifier-ref 'if) program statement linenumber))
    (else
			;;(display "this is where I should be")
			;;most other statements are (statement) (parameters)
	  		((identifier-ref (car statement)) (cdr statement))
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
        (run-program program (+ linenumber 1))
      ))
    )
  )
)





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

