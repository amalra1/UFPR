$:.push './'
require_relative '../ar.rb'

# Funcao que insere nas tabelas
def altera(words, nomeTabela)

    puts "Voce selecionou o(s) registro(s) que quer alterar, agora digite\nos novos atributos e valores que deseja para ele(s):";

    newInput = gets;
    newInput = newInput.force_encoding('UTF-8');

    # Separa as palavras com " ", preservando o que tem dentro de aspas, como no comeco
    newWords = newInput.scan(/(?:[^\s"]+|"[^"]*")+/);

    if (nomeTabela == "doctors" || nomeTabela == "hospitals" || nomeTabela == "bosses" || nomeTabela == "rooms")

        conditions = {};
        new_conditions = {};
	hospital_names = [];
	alteracao = "valida";

        if (words.length > 2)

            # Coloca os valores antigos na hash para buscar
            for i in 2...words.length

                oldAttribute, oldValue = words[i].split("=", 2);

                oldValue = oldValue.gsub(/"/, "");

                conditions[oldAttribute.to_sym] = oldValue;
            end

            # Coloca os valores novos em uma nova hash para substituir
            for i in 0...newWords.length

                attribute, value = newWords[i].split("=", 2);

                value = value.gsub(/"/, "");

		# Adiciona o nome do novo hospital para ser incluido na lista
		if (attribute == "hospitalName" && nomeTabela == "doctors")
                    hospital_names << value;
		end

                new_conditions[attribute.to_sym] = value;
            end

            # Localiza pela hash antiga e troca pelos valores da hash nova
            if (nomeTabela == "doctors")

		doctors = Doctor.where(conditions);

		# Adiciona um hospital a mais para o(s) doutor(es) desejado(s)
		doctors.each do |doctor|

		    hospitals = doctor.hospitals;

		    i = 0;

		    while (i < hospital_names.length)

  		        doctor.hospitals << Hospital.find_by_hospitalName(hospital_names[i]);
		        i += 1;
		    end
		end
		    
                Doctor.where(conditions).update_all(new_conditions);

	    elsif (nomeTabela == "hospitals")
                Hospital.where(conditions).update_all(new_conditions);
            elsif (nomeTabela == "bosses")

		# extrai o id de todos localizados pelas condicoes
		boss_ids = Boss.where(conditions).pluck(:id);
		old_hospital_name = Boss.where(id: boss_ids).first.hospitalName;

  		Boss.where(conditions).update_all(new_conditions);

		if (Hospital.find_by(hospitalName: Boss.where(new_conditions).first.hospitalName) == nil)
		    
		    puts "Voce alterou para um hospital nao adicionado, nao realizando alteracoes de hospital.";

		    # Altera o nome do hospital para os nomes anteriores
		    Boss.where(id: boss_ids).update_all(hospitalName: old_hospital_name);
		    alteracao = "invalida";

	    	else
		    # Aqui, pega o id do novo hospital para tambem alterar o relacionamento boss -> hospital
		    new_hospital = Hospital.find_by(hospitalName: Boss.where(new_conditions).first.hospitalName);
		    Boss.where(id: boss_ids).update_all(hospital_id: new_hospital.id);
		end

            elsif (nomeTabela == "rooms")
                Room.where(conditions).update_all(new_conditions);

		# extrai o id de todos localizados pelas condicoes
                room_ids = Room.where(conditions).pluck(:id);
                old_hospital_name = Room.where(id: room_ids).first.hospitalName;

                Room.where(conditions).update_all(new_conditions);

                if (Hospital.find_by(hospitalName: Room.where(new_conditions).first.hospitalName) == nil)

                    puts "Voce alterou para um hospital nao adicionado, nao realizando alteracoes de hospital.";

                    # Altera o nome do hospital para os nomes anteriores
                    Room.where(id: room_ids).update_all(hospitalName: old_hospital_name);
		    alteracao = "invalida";

                else
                    # Aqui, pega o id do novo hospital para tambem alterar o relacionamento boss -> hospital
                    new_hospital = Hospital.find_by(hospitalName: Room.where(new_conditions).first.hospitalName);
                    Room.where(id: room_ids).update_all(hospital_id: new_hospital.id);
                end
            end
        end

	if (alteracao == "valida")
            puts "Alteracoes realizadas.";
	else
	    puts "Alteracoes realizadas, mas hospital nao pode ser alterado.";
	end
    end
end
