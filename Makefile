
all: mod_mark.la

mod_mark.la: mod_mark.c
	apxs -c mod_mark.c

install: mod_mark.la
	apxs -i -a mod_mark.la

clean:
	$(RM) *.lo *.la *.slo
