class Boss < ActiveRecord::Base
    # Validacoes para insercao
    validates :fullName, :certifications, :phone, :department, :hospitalName, presence: true;
    validates :phone, numericality: { only_integer: true };

    belongs_to :hospital;
end
