; ModuleID = 'src/app.c'
source_filename = "src/app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.Circle = type { i32, i32, i32, i32, i32, i32 }

@g_circles = internal global [10 x %struct.Circle] [%struct.Circle { i32 480, i32 360, i32 1, i32 1, i32 100, i32 -12799119 }, %struct.Circle { i32 480, i32 360, i32 2, i32 3, i32 50, i32 -23296 }, %struct.Circle { i32 480, i32 360, i32 -4, i32 -1, i32 75, i32 -9807155 }, %struct.Circle { i32 480, i32 360, i32 -3, i32 4, i32 25, i32 -1146130 }, %struct.Circle { i32 480, i32 360, i32 -1, i32 3, i32 40, i32 -47975 }, %struct.Circle { i32 480, i32 360, i32 4, i32 5, i32 65, i32 -9063 }, %struct.Circle { i32 480, i32 360, i32 -5, i32 3, i32 98, i32 -16727297 }, %struct.Circle { i32 480, i32 360, i32 -4, i32 -6, i32 32, i32 -7673200 }, %struct.Circle { i32 480, i32 360, i32 -3, i32 2, i32 55, i32 -1401718 }, %struct.Circle { i32 480, i32 360, i32 -2, i32 3, i32 77, i32 -1172966 }], align 16

; Function Attrs: nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = tail call i32 (...) @simHandleEvents() #2
  %2 = icmp eq i32 %1, 0
  br i1 %2, label %3, label %42

3:                                                ; preds = %0, %39
  tail call void @simFillScreen(i32 noundef -15198184) #2
  br label %7

4:                                                ; preds = %36
  %5 = add nuw nsw i64 %8, 1
  %6 = icmp eq i64 %5, 10
  br i1 %6, label %39, label %7, !llvm.loop !5

7:                                                ; preds = %3, %4
  %8 = phi i64 [ 0, %3 ], [ %5, %4 ]
  %9 = getelementptr inbounds [10 x %struct.Circle], ptr @g_circles, i64 0, i64 %8
  %10 = load i32, ptr %9, align 8, !tbaa !7
  %11 = getelementptr inbounds [10 x %struct.Circle], ptr @g_circles, i64 0, i64 %8, i32 2
  %12 = load i32, ptr %11, align 8, !tbaa !12
  %13 = add nsw i32 %12, %10
  %14 = getelementptr inbounds [10 x %struct.Circle], ptr @g_circles, i64 0, i64 %8, i32 4
  %15 = load i32, ptr %14, align 8, !tbaa !13
  %16 = icmp slt i32 %13, %15
  %17 = add nsw i32 %13, %15
  %18 = icmp ugt i32 %17, 959
  %19 = select i1 %16, i1 true, i1 %18
  br i1 %19, label %20, label %22

20:                                               ; preds = %7
  %21 = sub nsw i32 0, %12
  store i32 %21, ptr %11, align 8, !tbaa !12
  br label %23

22:                                               ; preds = %7
  store i32 %13, ptr %9, align 8, !tbaa !7
  br label %23

23:                                               ; preds = %22, %20
  %24 = getelementptr inbounds [10 x %struct.Circle], ptr @g_circles, i64 0, i64 %8, i32 1
  %25 = load i32, ptr %24, align 4, !tbaa !14
  %26 = getelementptr inbounds [10 x %struct.Circle], ptr @g_circles, i64 0, i64 %8, i32 3
  %27 = load i32, ptr %26, align 4, !tbaa !15
  %28 = add nsw i32 %27, %25
  %29 = icmp slt i32 %28, %15
  %30 = add nsw i32 %28, %15
  %31 = icmp ugt i32 %30, 719
  %32 = select i1 %29, i1 true, i1 %31
  br i1 %32, label %33, label %35

33:                                               ; preds = %23
  %34 = sub nsw i32 0, %27
  store i32 %34, ptr %26, align 4, !tbaa !15
  br label %36

35:                                               ; preds = %23
  store i32 %28, ptr %24, align 4, !tbaa !14
  br label %36

36:                                               ; preds = %33, %35
  %37 = tail call i32 @simDrawCircle(ptr noundef nonnull %9) #2
  %38 = icmp eq i32 %37, 0
  br i1 %38, label %4, label %42

39:                                               ; preds = %4
  tail call void (...) @simFlush() #2
  %40 = tail call i32 (...) @simHandleEvents() #2
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %3, label %42

42:                                               ; preds = %39, %36, %0
  ret void
}

declare i32 @simHandleEvents(...) local_unnamed_addr #1

declare void @simFillScreen(i32 noundef) local_unnamed_addr #1

declare i32 @simDrawCircle(ptr noundef) local_unnamed_addr #1

declare void @simFlush(...) local_unnamed_addr #1

attributes #0 = { nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind }

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
