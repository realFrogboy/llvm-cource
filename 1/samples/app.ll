; ModuleID = 'src/app.c'
source_filename = "src/app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.Circle = type { i32, i32, i32, i32, i32, i32 }

@__const.app.circles = private unnamed_addr constant [10 x %struct.Circle] [%struct.Circle { i32 480, i32 360, i32 1, i32 1, i32 100, i32 -12799119 }, %struct.Circle { i32 480, i32 360, i32 2, i32 3, i32 50, i32 -23296 }, %struct.Circle { i32 480, i32 360, i32 -4, i32 -1, i32 75, i32 -9807155 }, %struct.Circle { i32 480, i32 360, i32 -3, i32 4, i32 25, i32 -1146130 }, %struct.Circle { i32 480, i32 360, i32 -1, i32 3, i32 40, i32 -47975 }, %struct.Circle { i32 480, i32 360, i32 4, i32 5, i32 65, i32 -9063 }, %struct.Circle { i32 480, i32 360, i32 -5, i32 3, i32 98, i32 -16727297 }, %struct.Circle { i32 480, i32 360, i32 -4, i32 -6, i32 32, i32 -7673200 }, %struct.Circle { i32 480, i32 360, i32 -3, i32 2, i32 55, i32 -1401718 }, %struct.Circle { i32 480, i32 360, i32 -2, i32 3, i32 77, i32 -1172966 }], align 16

; Function Attrs: nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = alloca [10 x %struct.Circle], align 16
  call void @llvm.lifetime.start.p0(i64 240, ptr nonnull %1) #4
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 16 dereferenceable(240) %1, ptr noundef nonnull align 16 dereferenceable(240) @__const.app.circles, i64 240, i1 false)
  %2 = tail call i32 (...) @simHandleEvents() #4
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %7, label %43

4:                                                ; preds = %8
  call void (...) @simFlush() #4
  %5 = call i32 (...) @simHandleEvents() #4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %7, label %43

7:                                                ; preds = %0, %4
  call void @simFillScreen(i32 noundef -15198184) #4
  br label %11

8:                                                ; preds = %40
  %9 = add nuw nsw i64 %12, 1
  %10 = icmp eq i64 %9, 10
  br i1 %10, label %4, label %11, !llvm.loop !5

11:                                               ; preds = %7, %8
  %12 = phi i64 [ 0, %7 ], [ %9, %8 ]
  %13 = getelementptr inbounds [10 x %struct.Circle], ptr %1, i64 0, i64 %12
  %14 = load i32, ptr %13, align 8, !tbaa !7
  %15 = getelementptr inbounds [10 x %struct.Circle], ptr %1, i64 0, i64 %12, i32 2
  %16 = load i32, ptr %15, align 8, !tbaa !12
  %17 = add nsw i32 %16, %14
  %18 = getelementptr inbounds [10 x %struct.Circle], ptr %1, i64 0, i64 %12, i32 4
  %19 = load i32, ptr %18, align 8, !tbaa !13
  %20 = icmp slt i32 %17, %19
  %21 = add nsw i32 %17, %19
  %22 = icmp ugt i32 %21, 959
  %23 = select i1 %20, i1 true, i1 %22
  br i1 %23, label %24, label %26

24:                                               ; preds = %11
  %25 = sub nsw i32 0, %16
  store i32 %25, ptr %15, align 8, !tbaa !12
  br label %27

26:                                               ; preds = %11
  store i32 %17, ptr %13, align 8, !tbaa !7
  br label %27

27:                                               ; preds = %26, %24
  %28 = getelementptr inbounds [10 x %struct.Circle], ptr %1, i64 0, i64 %12, i32 1
  %29 = load i32, ptr %28, align 4, !tbaa !14
  %30 = getelementptr inbounds [10 x %struct.Circle], ptr %1, i64 0, i64 %12, i32 3
  %31 = load i32, ptr %30, align 4, !tbaa !15
  %32 = add nsw i32 %31, %29
  %33 = icmp slt i32 %32, %19
  %34 = add nsw i32 %32, %19
  %35 = icmp ugt i32 %34, 719
  %36 = select i1 %33, i1 true, i1 %35
  br i1 %36, label %37, label %39

37:                                               ; preds = %27
  %38 = sub nsw i32 0, %31
  store i32 %38, ptr %30, align 4, !tbaa !15
  br label %40

39:                                               ; preds = %27
  store i32 %32, ptr %28, align 4, !tbaa !14
  br label %40

40:                                               ; preds = %37, %39
  %41 = call i32 @simDrawCircle(ptr noundef nonnull %13) #4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %8, label %43

43:                                               ; preds = %4, %40, %0
  call void @llvm.lifetime.end.p0(i64 240, ptr nonnull %1) #4
  ret void
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #2

declare i32 @simHandleEvents(...) local_unnamed_addr #3

declare void @simFillScreen(i32 noundef) local_unnamed_addr #3

declare i32 @simDrawCircle(ptr noundef) local_unnamed_addr #3

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

declare void @simFlush(...) local_unnamed_addr #3

attributes #0 = { nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #3 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 17.0.0 (https://github.com/llvm/llvm-project.git edcf3efd914409b2413c227fb333427585ea4957)"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = !{!8, !9, i64 0}
!8 = !{!"Circle", !9, i64 0, !9, i64 4, !9, i64 8, !9, i64 12, !9, i64 16, !9, i64 20}
!9 = !{!"int", !10, i64 0}
!10 = !{!"omnipotent char", !11, i64 0}
!11 = !{!"Simple C/C++ TBAA"}
!12 = !{!8, !9, i64 8}
!13 = !{!8, !9, i64 16}
!14 = !{!8, !9, i64 4}
!15 = !{!8, !9, i64 12}
