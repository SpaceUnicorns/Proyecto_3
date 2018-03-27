#pragma once 
#include "Transform.h"
#include <iostream>

Transform::Transform(Entidad * pEnt, int x, int y, int z, bool mainCharacter) : Componente(pEnt),mainCharacter(mainCharacter)
{
	this->x = x; this->y = y; this->z = z;
	camera = pEntidad->getPEstado()->getEntidad("MainCamera");
	Awake();
}
Transform::~Transform()
{
}
void Transform::Update(float deltaTime, Mensaje const & msj) {
	Componente::Update(deltaTime, msj);
	Mensaje msg = msj;
	if (mainCharacter && msg.getTipo() == Tipo::Input) {
		int pos = msg.getMsg().find("/");
		std::string xS = msg.getMsg().substr(0, pos);
		std::string subcad = msg.getMsg().substr(pos + 1);
		pos = subcad.find("/");
		std::string yS = subcad.substr(0, pos);
		std::string zS = subcad.substr(pos + 1);

		float x = std::stof(xS);
		float y = std::stof(yS);
		float z = std::stof(zS);

		this->x += x; this->z += z; this->y += y;

		Mensaje * m = new Mensaje(Tipo::Render, msg.getMsg(), SubTipo::Mover);
		//Si no se especifica receptor se considera broadcast
		m->setMsgInfo(pEntidad, pEntidad);
		pEntidad->getPEstado()->addMsg(*m);

		Mensaje * ms = new Mensaje(Tipo::Fisica, msg.getMsg(), SubTipo::Mover);
		//Si no se especifica receptor se considera broadcast
		ms->setMsgInfo(pEntidad, pEntidad);
		pEntidad->getPEstado()->addMsg(*ms);
	}
	if (msg.getTipo() == Tipo::Logica) {
		if (msg.getSubTipo() == SubTipo::Mover) {
			int pos = msg.getMsg().find("/");
			std::string xS = msg.getMsg().substr(0, pos);
			std::string subcad = msg.getMsg().substr(pos + 1);
			pos = subcad.find("/");
			std::string yS = subcad.substr(0, pos);
			std::string zS = subcad.substr(pos + 1);

			float x = std::stof(xS);
			float y = std::stof(yS);
			float z = std::stof(zS);

			this->x = x; this->z = z; this->y = y;
		}
	}
}

void Transform::Awake() {
	std::string msg = std::to_string(x) + "/" + std::to_string(y) + "/" + std::to_string(z);
	Mensaje * m = new Mensaje(Tipo::Fisica, msg, SubTipo::InitFis);
	//Si no se especifica receptor se considera broadcast
	m->setMsgInfo(pEntidad, pEntidad);
	pEntidad->getPEstado()->addMsg(*m);
}