

Για την μεταγλώττιση του find_roots_lib:
	μεταγλώττιση του roots.c χωρίς Linking
	πέρασμα στον archiver με εντολή ar rcs -libroots.a roots.o
	δημιουργία του find_roots_lib.c για να κληθεί η wrapper
	μεταγλώττιση τοu find_roots_lib (gcc find_roots_lib.c -o find_roots_lib -lroots -L.)

Για το module:
	μετακίνηση του original noop αρχείου και αλλάγη του κώδικα κατά τα γραφόμενα
	δημιουργία του Μakefile για να μπορέσει να γίνει η μεταγλώττιση του source αρχείου (από το project1-iosched.o)
	μεταγλώττιση του νέου module 
	ενσωμάτωση του module με insmod


_    _ _  _ _  _ _  _    ___  ____ _  _ _ _  _ ____ ___ ____ ____ 
|    | |\ | |  |  \/     |  \ |  | |\/| | |\ | |__|  |  |___ [__  
|___ | | \| |__| _/\_    |__/ |__| |  | | | \| |  |  |  |___ ___] 
                                                               
             d888888b. 
             8P"YP"Y88 
             8|o||o|88 
             8'    .88 
             8`._.' Y8. 
            d/      `8b. 
           dP   .    Y8b. 
          d8:'  "  `::88b 
         d8"         'Y88b 
        :8P    '      :888 
         8a.   :     _a88P 
       ._/"Yaa_:   .| 88P| 
       \    YP"    `| 8P  `.
       /     \.___.d|    .' 
       `--..__)8888P`._.' 
