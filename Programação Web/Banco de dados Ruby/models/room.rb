class Room < ActiveRecord::Base
    # Validacoes para insercao
    validates :bedQuantity, :roomNumber, :floor, :readyForUse, :hospitalName, presence: true;
    validates :roomNumber, :bedQuantity, numericality: { only_integer: true };

    belongs_to :hospital;
end
