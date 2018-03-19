#pragma once
#include "Componente.h"
#include <iterator>
#include "Mensaje.h"

class Estado;

class Entidad{

public:
	Entidad(Estado* pEstado);
	Entidad(Estado* pEstado, std::string prefab);
	void Update(float deltaTime, Mensaje const & msg);
	void Awake();
	void Sleep();
	Estado* getPEstado() { return pEstado; };

	bool aņadeComponenteGrafico(std::string mesh);
	bool aņadeComponenteFisico();
	bool aņadeAnimacion(std::string mesh);
	bool aņadeComponenteLogico(std::string component);
private:
	std::map<std::string, Componente*> componentes;
	Estado* pEstado;
	bool activo;

};