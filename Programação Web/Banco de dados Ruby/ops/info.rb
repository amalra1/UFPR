$:.push './'
require_relative '../ar.rb'

# Funcao que insere nas tabelas
def info()    

	puts "========================================================================================="
        print "Tabela 'Doctors' -> atributos: :name, :lastName, :area, :phone, :admissionYear e :hospitalName\n";
        print "!:phone e admissionYear precisam ser numeros!\n";
	print "!:hospitalName indica a que hospital esse doutor sera relacionado.\n\n";


        print "Tabela 'Hospitals' -> atributos: :hospitalName, :address\n\n";

        print "Tabela 'Bosses' -> atributos: :fullName, :department, :certifications, :phone, :hospitalName\n";
        print "!:phone precisa ser um numero!\n";
	print "!:hospitalName indica a que hospital esse boss sera relacionado.\n\n";

        print "Tabela 'Rooms' -> atributos: :roomNumber, :floor, :bedQuantity, :readyForUse, :hospitalName\n";
        print "!:roomNumber e bedQuantity precisam ser numeros!\n";
	print "!:hospitalName indica a que hospital essas rooms serao relacionadas.\n\n";

	print "Comandos funcionam desta maneira: < operacao > < tabela > { atributo=\"valor\" } { atributo=... } ...\n"
 	print "=========================================================================================\n\n"
    end
