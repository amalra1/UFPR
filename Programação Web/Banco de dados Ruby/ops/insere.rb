$:.push './'
require_relative '../ar.rb'

# Funcao que insere nas tabelas
def insere(input, nomeTabela)

    insercao = "valida";
    
    if (nomeTabela == "doctors")

        new_line = Doctor.new();

        # Pega os valores dos atributos
	new_line.name = extrai_valor_atributo(input, "name");
        new_line.lastName = extrai_valor_atributo(input, "lastName");
        new_line.area = extrai_valor_atributo(input, "area");
        new_line.phone = extrai_valor_atributo(input, "phone");
        new_line.admissionYear = extrai_valor_atributo(input, "admissionYear");
	new_line.hospitalName = extrai_valor_atributo(input, "hospitalName");

	# Procurando hospital no banco
	hospital = Hospital.find_by_hospitalName(new_line.hospitalName);

	if (hospital != nil)

            # E associa

            new_line.hospitals << hospital;

        else
           puts "O hospital escrito nao esta no banco de dados! O insira primeiro";

           insercao = "invalida";
        end

     elsif (nomeTabela == "hospitals")

        new_line = Hospital.new();

        # Pega os valores dos atributos
        new_line.hospitalName = extrai_valor_atributo(input, "hospitalName");
        new_line.address = extrai_valor_atributo(input, "address");

     elsif (nomeTabela == "bosses")

        new_line = Boss.new();

        # Pega os valores dos atributos
        new_line.fullName = extrai_valor_atributo(input, "fullName");
        new_line.certifications = extrai_valor_atributo(input, "certifications");
        new_line.phone = extrai_valor_atributo(input, "phone");
        new_line.department = extrai_valor_atributo(input, "department");

	# Agora pega o hospital que ele esta relacionado
	new_line.hospitalName = extrai_valor_atributo(input, "hospitalName");

	hospital = Hospital.find_by(hospitalName: new_line.hospitalName);

	if (hospital != nil)

	    # E associa
	    new_line.hospital = hospital;
	else
	   puts "O hospital escrito nao esta no banco de dados! O insira primeiro";

	   insercao = "invalida";
	end

     elsif (nomeTabela == "rooms")

        new_line = Room.new();

        # Pega os valores dos atributos
        new_line.roomNumber = extrai_valor_atributo(input, "roomNumber");
        new_line.floor = extrai_valor_atributo(input, "floor");
        new_line.bedQuantity = extrai_valor_atributo(input, "bedQuantity");
        new_line.readyForUse = extrai_valor_atributo(input, "readyForUse");

	# Agora pega o hospital que a room esta relacionada
	new_line.hospitalName = extrai_valor_atributo(input, "hospitalName");

	hospital = Hospital.find_by(hospitalName: new_line.hospitalName);

        if (hospital != nil)

            # E associa
            new_line.hospital = hospital;
        else
           puts "O hospital escrito nao esta no banco de dados! O insira primeiro";

           insercao = "invalida";
        end
     end

    # Verifica se as validacoes foram seguidas
    if (new_line.valid? && insercao == "valida")
        puts "Inserido na tabela";
	new_line.save;
    else
        puts "Nao foi possivel inserir, insira corretamente com todos os atributos";
    end
end
