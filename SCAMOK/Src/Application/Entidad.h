#pragma once
#include "Componente.h"
#include <iterator>
#include "Mensaje.h"
#include <vector>


class Estado;
class Entidad{

public:
	Entidad(Estado* pEstado);
	Entidad(Estado* pEstado, std::string prefab, std::string nombre = "");
	~Entidad();
	void Update(float deltaTime, Mensaje  & msg);
	void Awake();
	void Sleep();
	Estado* getPEstado() { return pEstado; };

	bool aņadeComponenteGrafico(std::string mesh);
	bool aņadeComponenteGrafico(std::string mesh, std::string ogreNodeName);
	bool aņadeComponenteFisico(float altoCaja, float anchoCaja, float profCaja, bool suelo, tipoFisica type = tipoFisica::Estatico, int masa = 0);
	bool aņadeAnimacion(std::string mesh, std::ifstream & fe);
	bool aņadeAnimacion(std::string name,bool enabled = true, bool loop = true);
	bool aņadeComponenteLogico(std::string component);
	bool aņadeComponenteSM(std::string component, void* sys);
	void setAnim(std::string const &s, bool loop = false, bool enabled = true, bool idle = false);
	void destruyeComponenteGrafico();
	void destroy() {
		for (std::pair<std::string, Componente*> p : componentes) {
			delete p.second;
		}
	};
	std::string getNombreNodo() { return nombreNodo; };
	void setNombreNodo(std::string s) { nombreNodo = s; };
	int cont = 0;
	Componente* getComponente(std::string const & name) {
		return componentes.at(name);
	}

private:
	std::map<std::string, Componente*> componentes;
	Estado* pEstado;
	bool activo;
	Entidad* target; //Usar esta entidad para escuchar los mensajes dirigidos a ella
	std::string nombreNodo;
	
};