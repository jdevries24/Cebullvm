include "mlir/IR/PatternBase.td"
include "mlir/Dialect/Shape/IR/ShapeOps.td"
include "mlir/Dialect/Tensor/IR/TensorOps.td"

def AllInputShapesEq : Constraint<CPred< [{
  llvm::all_equal($0)
}]>>;

def HasSingleElement : Constraint<CPred< [{
  $0.size() == 1
}]>>;

def HasStaticShape : Constraint<CPred< [{
  ::llvm::dyn_cast<ShapedType>($0.getType()).hasStaticShape()
}]>>;

// Helper that takes the first element of a range.
def TakeFront : NativeCodeCall<"$0.front()">;

// Canonicalization patterns.

def AssumingAllOneOp : Pat<(Shape_AssumingAllOp $args),
                           (replaceWithValue $args),
                           [(HasSingleElement $args)]>;

def CstrBroadcastableEqOps : Pat<(Shape_CstrBroadcastableOp:$op $shapes),
  (Shape_ConstWitnessOp ConstBoolAttrTrue),
  [(AllInputShapesEq $shapes)]>;

def CstrEqEqOps : Pat<(Shape_CstrEqOp:$op $shapes),
  (Shape_ConstWitnessOp ConstBoolAttrTrue),
  [(AllInputShapesEq $shapes)]>;

def IndexToSizeToIndexCanonicalization : Pat<
  (Shape_SizeToIndexOp (Shape_IndexToSizeOp $arg)),
  (replaceWithValue $arg)>;

def SizeToIndexToSizeCanonicalization : Pat<
  (Shape_IndexToSizeOp (Shape_SizeToIndexOp $arg)),
  (replaceWithValue $arg)>;

// Fold tensor.cast(const_shape) to const_shape. This changes the type of
// const_shape to the destination type of the cast.
def TensorCastConstShape : Pat <
  (Tensor_CastOp:$res (Shape_ConstShapeOp $arg)), (Shape_ConstShapeOp $arg),
  [(HasStaticShape $res)]>;

// tensor.extract from shape_of -> tensor.dim. We can take the first index
// because shape_of always returns a 1D tensor.
def ExtractFromShapeOfExtentTensor : Pat<
  (Tensor_ExtractOp (Shape_ShapeOfOp $arg), $indices),
  (Tensor_DimOp $arg, (TakeFront $indices))>;
