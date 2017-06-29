unit DealType;

interface
Const MAX_STR_LEN = 20;

Const MIN_YEAR = 1950;
Const MAX_YEAR = 2050;

Const MASK_TOMBSTONE = 0;
Const MASK_IMPORT    = 1;
Const MASK_EXPORT    = 2;
Const MASK_ANY       = 3;

Type
  DealT = record
    product: string[MAX_STR_LEN];
    volume:  Integer;
    year:    Word; // or next tombstone for MASK_TOMBSTONE, 0 if none
    country: string[MAX_STR_LEN];
    mask:    Byte;
  end;

const nullDeal: DealT = (
  product:  chr(0);
  volume:        0;
  year:          0;
  country:  chr(0);
  mask:   MASK_ANY;
);

function DealCmp(a: DealT; b: DealT): Boolean;
implementation
function DealCmp;
begin
  Result := ((a.product = nullDeal.product) or
           (a.product =     b.product))    and
          ((a.volume  = nullDeal.volume ) or
           (a.volume  =     b.volume ))    and
          ((a.year    = nullDeal.year   ) or
           (a.year    =     b.year   ))    and
          ((a.country = nullDeal.country) or
           (a.country = b.country    ))    and
          (a.mask and b.mask <> 0)        ;
end;
end.
