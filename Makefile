subsystem:
	$(MAKE) -C ./src
clean:
	cd ./src && $(MAKE) clean
cleanall:
	cd ./src && $(MAKE) cleanall
	rm -rf ./latex ./html *log* 
