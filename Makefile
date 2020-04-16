OUTDIR   = out
DISTDIR  = ${OUTDIR}/reset
LOCALBIN = ${DISTDIR}/usr/local/bin
BUILDDIR = ${OUTDIR}/build
SPECDIR  = ${OUTDIR}
PYSRCDIR = .

dist:
	mkdir -p ${OUTDIR}
	pyinstaller \
		--distpath ${DISTDIR} \
		--workpath ${BUILDDIR} \
		--specpath ${SPECDIR} \
		-p ${PYSRCDIR} \
		-p ${PYSRCDIR}/arduino \
		-F \
		--hidden-import	usb \
		-n usbreset \
		--log-level DEBUG \
		usbreset.py

clean:
	rm -f *.pyc
	rm -rf __pycache__

distclean: clean
	rm -f *.deb
	rm -rf ${OUTDIR}
