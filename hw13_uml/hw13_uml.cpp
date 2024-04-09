#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Processor;
class Hdd;
class RAM;
class GPU;

class IVisitor abstract
{
public:
	virtual void VisitProcessor(Processor* proc) abstract;
	virtual void VisitHdd(Hdd* hdd) abstract;
	virtual void VisitRAM(RAM* ram) abstract;
	virtual void VisitGPU(GPU* gpu) abstract;
};

class AbstractDevice abstract
{
	string Producer;
public:
	virtual void Accept(IVisitor* visitor)abstract;
	string GetProducer()
	{
		return Producer;
	}
	void SetProducer(string Producer)
	{
		this->Producer = Producer;
	}
};

class Processor : public AbstractDevice
{
	string Frequency;
	string CoreCount;
public:
	string GetFrequency()
	{
		return  Frequency;
	}
	void SetFrequency(string Frequency)
	{
		this->Frequency = Frequency;
	}
	string GetCoreCount()
	{
		return CoreCount;
	}
	void SetCoreCount(string CoreCount)
	{
		this->CoreCount = CoreCount;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitProcessor(this);
	}
};

class Hdd : public AbstractDevice
{
	string Volume;
	string Type;
public:
	string GetVolume()
	{
		return Volume;
	}
	void SetVolume(string Volume)
	{
		this->Volume = Volume;
	}
	string GetType()
	{
		return Type;
	}
	void SetType(string Type)
	{
		this->Type = Type;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitHdd(this);
	}
};


class RAM : public AbstractDevice
{
	string type;
	int capacity;
	int frequency;
public:
	int getFrequency()
	{
		return  frequency;
	}
	void setFrequency(int Frequency)
	{
		this->frequency = frequency;
	}
	string getType()
	{
		return type;
	}
	void setType(string type)
	{
		this->type = type;
	}
	int getCapacity() {
		return capacity;
	}
	void setCapacity(int capacity) {
		this->capacity = capacity;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitRAM(this);
	}
};

class GPU : public AbstractDevice
{
	string model;
	int coreCount; //количество ядер
	double coreClock; //частота ядра
public:
	string getModel()
	{
		return  model;
	}

	void setModel(string model)
	{
		this->model = model;
	}

	void setCoreCount(int count)
	{
		this->coreCount = coreCount;
	}
	int getCoreCount()
	{
		return coreCount;
	}
	double getCoreClock() {
		return coreClock;
	}
	void setCoreClock(double coreClock) {
		this->coreClock = coreClock;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitGPU(this);
	}
};

// сериализатор в HTML
class HtmlVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + proc->GetProducer() + "</td></tr>";
		result += "<tr><td>Frequency<td><td>" + proc->GetFrequency() + "</td></tr>";
		result += "<tr><td>CoreCount<td><td>" + proc->GetCoreCount() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + hdd->GetProducer() + "</td></tr>";
		result += "<tr><td>Type<td><td>" + hdd->GetType() + "</td></tr>";
		result += "<tr><td>Volume<td><td>" + hdd->GetVolume() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}

	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + ram->GetProducer() + "</td></tr>";
		result += "<tr><td>Type<td><td>" + ram->getType() + "</td></tr>";
		result += "<tr><td>Capacity<td><td>" + to_string(ram->getCapacity()) + "</td></tr>";
		result += "<tr><td>Frequency<td><td>" + to_string(ram->getFrequency()) + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}

	void VisitGPU(GPU* gpu) override
	{
		ofstream out("RAM.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + gpu->GetProducer() + "</td></tr>";
		result += "<tr><td>Model<td><td>" + gpu->getModel() + "</td></tr>";
		result += "<tr><td>Core clock<td><td>" + to_string(gpu->getCoreClock()) + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

// сериализатор в XML
class XmlVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<Processor><Producer>" + proc->GetProducer() + "</Producer>" +
			"<Frequency>" + proc->GetFrequency() + "</Frequency>" +
			"<CoreCount>" + proc->GetCoreCount() + "</CoreCount></Processor>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<HDD><Producer>" + hdd->GetProducer() + "</Producer>" +
			"<Type>" + hdd->GetType() + "</Type>" +
			"<Volume>" + hdd->GetVolume() + "</Volume></HDD>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<RAM><Producer>" + ram->GetProducer() + "</Producer>" +
			"<Type>" + ram->getType() + "</Type>" +
			"<Frequency>" + to_string(ram->getFrequency()) + "</Frequency>" + "<Capacity>"
			+ to_string(ram->getCapacity()) + "</Capacity></RAM>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitGPU(GPU* gpu) override
	{
		ofstream out("GPU.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<GPU><Producer>" + gpu->GetProducer() + "</Producer>" +
			"<Model>" + gpu->getModel() + "</Model>" +
			"<CoreClock>" + to_string(gpu->getCoreClock()) + "</CoreClock>" + "<CoreCount>"
			+ to_string(gpu->getCoreCount()) + "</CoureCount> </GPU> ";
			out.write(result.c_str(), result.size());
		out.close();
	}
};

// сериализатор в TEXT
class TextVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.txt", ios::binary | ios::trunc | ios::out);
		string result = "";
		result += "Processor: \n Producer:" + proc->GetProducer() + "\n" +
			"Frequency:" + proc->GetFrequency() + "\n" +
			"Core Count: " + proc->GetCoreCount() + "\n";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.txt", ios::binary | ios::trunc | ios::out);
		string result = "";
		result += "Producer: " + hdd->GetProducer() + "\n" +
			"Type: " + hdd->GetType() + "\n" +
			"Volume: " + hdd->GetVolume() + "\n";
		out.write(result.c_str(), result.size());
		out.close();
	}

	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.txt", ios::binary | ios::trunc | ios::out);
		string result = "";
		result += "Producer: " + ram->GetProducer() + "\n" +
			"Type: " + ram->getType() + "\n" +
			"Frequency: " + to_string(ram->getFrequency()) + "\n" +
			"Capacity: " + to_string(ram->getCapacity()) + "\n";
		out.write(result.c_str(), result.size());
		out.close();
	}

	void VisitGPU(GPU* gpu) override
	{
		ofstream out("GPU.txt", ios::binary | ios::trunc | ios::out);
		string result = "";
		result += "Producer: " + gpu->GetProducer() + "\n" +
			"Model: " + gpu->getModel() + "\n" +
			"Core clock: " + to_string(gpu->getCoreClock()) + "\n" +
			"Core count: " + to_string(gpu->getCoreCount()) + "\n";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

// сериализатор в Console
class ConsoleVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		cout << "Processor" << endl;
		cout << "Producer: " << proc->GetProducer() << endl;
		cout << "Frequency: " << proc->GetFrequency() << endl;
		cout << "Core Count: " << proc->GetCoreCount() << endl;
		cout << endl;
	}
	void VisitHdd(Hdd* hdd) override
	{
		cout << "HDD" << endl;
		cout << "Producer: " << hdd->GetType() << endl;
		cout << "Type: " << hdd->GetVolume() << endl;
		cout << "Volume: " << hdd->GetVolume() << endl;
	}

	void VisitRAM(RAM* ram) override
	{
		cout << "RAM" << endl;
		cout << "Producer: " << ram->GetProducer() << endl;
		cout << "Type: " << ram->getType() << endl;
		cout << "Frequency: " << ram->getFrequency() << endl;
		cout << "Capacity: " << ram->getCapacity() << endl;
		cout << endl;
	}

	void VisitGPU(GPU* gpu) override
	{
		cout << "GPU" << endl;
		cout << "Producer: " << gpu->GetProducer() << endl;
		cout << "Model: " << gpu->getModel() << endl;
		cout << "Core clock: " << gpu->getCoreClock() << endl;
		cout << "Core count: " << gpu->getCoreCount() << endl;
	}
};

class PC
{
	vector<AbstractDevice*> devices;
public:
	void Add(AbstractDevice* d)
	{
		devices.push_back(d);
	}
	void Remove(AbstractDevice* d)
	{
		auto iter = find(devices.begin(), devices.end(), d);
		if (iter != devices.end())
			devices.erase(iter);
	}
	void Accept(IVisitor* visitor)
	{
		for (AbstractDevice* d : devices)
			d->Accept(visitor);
	}
};

int main()
{
	PC* pc = new PC();
	Processor* p = new Processor;
	p->SetProducer("Intel");
	p->SetFrequency("3.5");
	p->SetCoreCount("4");
	pc->Add(p);

	Hdd* hdd = new Hdd;
	hdd->SetProducer("Western Digital");
	hdd->SetType("SATA III");
	hdd->SetVolume("2");
	pc->Add(hdd);

	RAM* ram = new RAM;
	ram->SetProducer("Corsair");
	ram->setType("DDR4");
	ram->setFrequency(3200);
	ram->setCapacity(16);  
	pc->Add(ram);
	
	GPU* gpu = new GPU;
	gpu->SetProducer("NVIDIA");
	gpu->setModel("GeForce RTX 3080");
	gpu->setCoreClock(1440);
	gpu->setCoreCount(8704);
	pc->Add(gpu);

	HtmlVisitor* html = new HtmlVisitor;
	pc->Accept(html);
	XmlVisitor* xml = new XmlVisitor;
	pc->Accept(xml);
	TextVisitor* text = new TextVisitor;
	pc->Accept(text);
	ConsoleVisitor* console = new ConsoleVisitor;
	pc->Accept(console);
	delete html;
	delete xml;
	delete text;
	delete console;
	delete hdd;
	delete ram;
	delete gpu;
	delete p;
	delete pc;

	system("pause");
}
