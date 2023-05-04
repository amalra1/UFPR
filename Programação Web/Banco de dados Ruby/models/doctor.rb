class Doctor < ActiveRecord::Base
    # Validacoes para insercao
    validates :name, :lastName, :phone, :area, :admissionYear, :hospitalName, presence: true;
    validates :phone, :admissionYear, numericality: { only_integer: true };

    has_and_belongs_to_many :hospitals#, -> { uniq };
end

