# Carrega as bibliotecas e arquivos
require 'rubygems'
require 'active_record'
require 'sqlite3'

# Carrega os objetos do ActiveRecord::Base.
require_relative 'models/doctor.rb'
require_relative 'models/hospital.rb'
require_relative 'models/boss.rb'
require_relative 'models/room.rb'

# Estabelece a conexao com o banco de dados sqlite3.
ActiveRecord::Base.establish_connection :adapter => 'sqlite3', :database => 'db/tabelas.sqlite3'

# Codigo para criar as tabelas
# Doctor
if (!ActiveRecord::Base.connection.table_exists?(:doctors))
    ActiveRecord::Base.connection.create_table :doctors do |t|
        t.string :name;
        t.string :lastName;
        t.string :phone;
	t.string :area;
	t.string :admissionYear;
	t.string :hospitalName;
    end
end

# Hospital
if (!ActiveRecord::Base.connection.table_exists?(:hospitals))
    ActiveRecord::Base.connection.create_table :hospitals do |t|
        t.string :hospitalName;
        t.string :address;
    end
end

# Tabela intermediaria DoctorsHospitals
if (!ActiveRecord::Base.connection.table_exists?(:doctors_hospitals))
    ActiveRecord::Base.connection.create_table :doctors_hospitals, id: false do |t|
        t.references :hospital;
        t.references :doctor;
    end
end

# Boss
if (!ActiveRecord::Base.connection.table_exists?(:bosses))
    ActiveRecord::Base.connection.create_table :bosses do |t|
        t.string :fullName;
        t.string :certifications;
	t.string :phone;
	t.string :department;
	t.string :hospitalName;

	t.references :hospital, foreign_key: true;	
    end
end

# Room
if (!ActiveRecord::Base.connection.table_exists?(:rooms))
    ActiveRecord::Base.connection.create_table :rooms do |t|
	t.string :bedQuantity;
        t.string :roomNumber;
        t.string :floor;
        t.string :readyForUse;
	t.string :hospitalName;

	t.references :hospital, foreign_key: true;
    end
end
