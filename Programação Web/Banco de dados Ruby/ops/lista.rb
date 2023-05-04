$:.push './'
require_relative '../ar.rb'

# Funcao que lista os doctors
def lista(nomeTabela)
    
    if (nomeTabela == "doctors")

        print "Listando linhas da tabela 'doctors':\n\n"

        all_docs = Doctor.all;
        i = 1;

        all_docs.each do |doctor|
            print "#{i}|"
            print "name = #{doctor.name}|";
            print "last name = #{doctor.lastName}|";
            print "area = #{doctor.area}|";
            print "admissionYear = #{doctor.admissionYear}|";
            print "phone = #{doctor.phone}\n";
	    print "hospitais relacionados:\n";

	    # Pega todos os hospitais que o doctor trabalha
	    hospitals = doctor.hospitals;

	    hospitals.each do |hospital|
	        print "#{hospital.hospitalName}\n";
	    end
	    puts;	    

            i += 1;
        end

    elsif (nomeTabela == "hospitals")

        print "Listando linhas da tabela 'hospitals':\n\n"

        all_hospitals = Hospital.all;
        i = 1;

        all_hospitals.each do |hospital|
                print "#{i}|"
                print "HospitalName = #{hospital.hospitalName}|";
                print "address = #{hospital.address}\n";
		print "doutores residentes:\n";

            	# Pega todos os doutores do hospital
            	doctors = hospital.doctors;

            	doctors.each do |doctor|
		    print "#{doctor.name} #{doctor.lastName}\n";
            	end
            	puts;

                i += 1;
        end

     elsif (nomeTabela == "bosses")

        print "Listando linhas da tabela 'bosses':\n\n"

        all_bosses = Boss.all;
        i = 1;

        all_bosses.each do |boss|
                print "#{i}|"
                print "fullName = #{boss.fullName}|";
                print "department = #{boss.department}|";
                print "certifications = #{boss.certifications}|";
                print "phone = #{boss.phone}\n";
		print "hospital relacionado:\n#{boss.hospital.hospitalName}\n\n";
                i += 1;
      	end

     elsif (nomeTabela == "rooms")

        print "Listando linhas da tabela 'rooms':\n\n"

        all_rooms = Room.all;
        i = 1;

        all_rooms.each do |room|
                print "#{i}|"
                print "room number = #{room.roomNumber}|";
                print "floor = #{room.floor}|";
                print "bed quantity = #{room.bedQuantity}|";
                print "ready for use? = #{room.readyForUse}\n";
		print "hospital relacionado:\n#{room.hospital.hospitalName}\n\n";

                i += 1;
        end
     end
end
