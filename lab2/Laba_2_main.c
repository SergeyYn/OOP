#include "Laba_2_Head.h"

int main() {
	create_db("scanners.csv", "scanners.db");
	print_db("scanners.db");
	make_index("scanners.db", "year");
	reindex("scanners.db");
	add_scanner("scanners.db", "ASUS;AS1055;2009;99.99;210;297");
	print_db("scanners.db");
	del_scanner("scanners.db", 5);
	print_db("scanners.db");
	RECORD_SET* rs = select("scanners.db", "manufacturer", "ASUS");
	print_rec_set(rs);
	rs = get_recs_by_index("scanners.db", "price");
	print_rec_set(rs);
	return 0;
}
