class Hospital < ActiveRecord::Base
    # Validacoes para insercao
    validates :hospitalName, :address, presence: true;

    has_one :boss, dependent: :destroy
    has_many :rooms, dependent: :destroy;
    has_and_belongs_to_many :doctors, dependent: :destroy;

    def boss_name
        boss.present? ? boss.fullName : "Nenhum boss neste hospital ainda";
    end
end
