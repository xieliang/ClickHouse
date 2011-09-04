#pragma once

#include <Poco/SharedPtr.h>

#include <DB/DataStreams/IProfilingBlockInputStream.h>


namespace DB
{

using Poco::SharedPtr;


/** Реализует операции WHERE, HAVING.
  * На вход подаётся поток блоков, в котором в одном из столбцов типа ColumnUInt8 содержатся условия фильтрации.
  * Возвращается поток блоков, в котором содержатся только отфильтрованные строки.
  */
class FilterBlockInputStream : public IProfilingBlockInputStream
{
public:
	/// filter_column_ - номер столбца с условиями фильтрации. -1 - последний столбец
	FilterBlockInputStream(BlockInputStreamPtr input_, ssize_t filter_column_ = -1);
	Block readImpl();

	String getName() const { return "FilterBlockInputStream"; }

private:
	BlockInputStreamPtr input;
	ssize_t filter_column;
};

}
