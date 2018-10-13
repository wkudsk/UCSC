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
        (hash-ref lblhash key #f))

(define (insert-label key value)
        (hash-set! lblhash key value))

(define (get-statement key)
        (hash-ref stthash key #f))

(define (insert-statement key value)
        (hash-set! stthash key value))

(define (get-variable key)
        (hash-ref varhash key #f))

(define (insert-variable key value)
        (hash-set! *variable-table* key value))

(for-each
      (lambda (item) (hash-set! stthash (car item) (cadr item)))
        `((print , my-print)))

(define (interpret-program program) 
  (when (not (null? program))
              (let ((linenumber (caar program)))
                   (when (and (number? linenumber) (not (null? (cdar program))) (symbol? (cadar program)))
                      (insert-label (cadar program) (caar program))))
              (interpret-program (cdr program))))

(define (execute-statement sttname program)
  )

(define (run-program program)
  )

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
              (write-program-by-line sbprogfile program)
              (interpret-program program))))

(when (terminal-port? *stdin*)
      (main (vector->list (current-command-line-arguments))))

